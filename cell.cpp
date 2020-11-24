#include "cell.h"
#include "node.h"
#include "parser.h"
#include "lexer.h"
#include <QDebug>
#include"tree.h"

Cell::Cell(QTableWidget* parent) : isEmpty(true)
{
    qDebug() << "creating cell";
    setDirty();
    tree = new Tree(this);
    this->parent = parent;
    cellsThatRef.resize(0);
    cellsINFormula.resize(0);
    colour = 0;
}



Cell::~Cell()
{
    delete tree;
}


void Cell::setDirty()
{
    cacheIsDirty = true;
}

bool Cell::getIsEmpty() const
{
    return isEmpty;
}

void Cell::recalculate()
{
    //setData(Qt::EditRole, formula);
    tree->recalculate();

    if(static_cast<Spreadsheet*>(parent)->cycleDetector(this))
    {
        qDebug() << "cycle";
        return;
    }

    for(auto& el : cellsThatRef)
    {
        el->recalculate();
    }

    setData(Qt::DisplayRole, getValue());
}

QVariant Cell::getAnotherCellData(int row, int column) const
{
    qDebug() << row << " " << column;
    if(parent->item(row,column) == nullptr)
    {
        parent->setItem(row,column, new Cell(parent));
        parent->item(row,column)->setData(Qt::DisplayRole, "Empty");

    }
    return parent->item(row,column)->data(Qt::DisplayRole);
}


QTableWidgetItem *Cell::clone() const
{
    qDebug() << "clone";
    return new Cell(parent);

}


QVariant Cell::data(int role) const
{

        if(role ==Qt::DisplayRole)
        {

                return getValue();

         }

        return QTableWidgetItem::data(role);
}

void Cell::setData(int role, const QVariant &value)
{

    if(role == Qt::EditRole)
    {

        for(auto& el : this->cellsINFormula)
        {
            el->cellsThatRef.removeAll(this);
        }

        cellsINFormula.clear();

        formula = value.toString();

        auto tokens = Lexer::Tokenize(value.toString());

        for(const auto& el : tokens)
        {
            if(el.getType() == TokenType::kCell)
            {
               std::pair<int, int> coords = coordByLink(el.GetLexema());
               getAnotherCellData(coords.first,coords.second);
               Cell* cell = static_cast<Cell*>(parent->item(coords.first, coords.second));
               this->cellsINFormula.push_back(cell);
               cell->cellsThatRef.push_back(this);

            }
        }


        tree->setHead(Parser::parse(tokens));

        if(static_cast<Spreadsheet*>(parent)->cycleDetector(this))
        {
            qDebug() << "cycle";

            if(this->data(Qt::DisplayRole) == "")
            {
                isEmpty = true;
            }
            else
            {
                isEmpty = false;
            }


                setDirty();


            return;
        }

        QTableWidgetItem::setData(role, value);



        if(this->data(Qt::DisplayRole) == "")
        {
            isEmpty = true;
        }
        else
        {
            isEmpty = false;
        }

        for(auto& el : cellsThatRef)
        {

            el->recalculate();
        }

            setDirty();
}

    else if(role == Qt::DisplayRole)
    {
        QTableWidgetItem::setData(Qt::DisplayRole, value);
    }
}

void Cell::setFormula(const QString &formula)
{
     setData(Qt::EditRole, formula);

}

QString Cell::getFormula() const
{
   //return data(Qt::EditRole).toString();
    return formula;
}


QString Cell::getValue() const
{

    return tree->getResult();
}

std::pair<int, int> Cell::coordByLink(const QString &link) const
{
    QString column;
    QString row;
    for(int i =0 ; i < link.length(); ++i)
    {
        if(link[i].unicode() >= QChar('A').unicode() && link[i].unicode() <= QChar('Z').unicode())
        {
           column.push_back(link[i]);
        } else {
           row.push_back(link[i]);
        }
    }
    int rowNum = row.toInt();
    int columnNum = 0;
    for(int i = column.length()-1; i >= 0; --i)
    {
        columnNum += std::pow(26, column.length() - 1 - i)*(column[i].unicode() - QChar('A').unicode() + 1);
    }
    --rowNum;
    --columnNum;
    return std::make_pair(rowNum, columnNum);
}

QTableWidget* Cell::getParent()
{
    return parent;
}
