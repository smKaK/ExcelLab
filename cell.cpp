#include "cell.h"
#include "node.h"
#include "parser.h"
#include "lexer.h"
#include <QDebug>
#include"tree.h"

Cell::Cell(QTableWidget* parent) : isEmpty(true), colour(0), parent(parent)
{
    setDirty();
    tree = new Tree(this);
    cellsThatRef.resize(0);
    cellsINFormula.resize(0);
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

QVector<Cell *> Cell::getCellsThatRefs() const
{
    return cellsThatRef;
}

QVector<Cell *>& Cell::getCellsThatRefs()
{
    return cellsThatRef;
}


QTableWidgetItem *Cell::clone() const
{
    return new Cell(parent);

}

int Cell::getColour() const
{
    return colour;
}

void Cell::setColour(int newColour)
{
    colour = newColour;
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
      //updating references
        for(auto& el : this->cellsINFormula)
        {
            el->getCellsThatRefs().removeAll(this);
        }

        cellsINFormula.clear();



        formula = value.toString();

        auto tokens = Lexer::Tokenize(value.toString());

        //detecting cell references in new formula
        for(const auto& el : tokens)
        {
            if(el.getType() == TokenType::kCell)
            {
               std::pair<int, int> coords = coordByLink(el.GetLexema());
               if(coords.first != -1)
               {
                   Cell* cell = static_cast<Cell*>(parent->item(coords.first, coords.second));
                   this->cellsINFormula.push_back(cell);
                   cell->cellsThatRef.push_back(this);

               }
            }
        }

        //parsing and cycle detecting
        tree->setHead(Parser::parse(tokens));
        if(static_cast<Spreadsheet*>(parent)->cycleDetector(this))
        {

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

        //setting data
        QTableWidgetItem::setData(role, value);


        // checking display role data
        if(this->data(Qt::DisplayRole) == "")
        {
            isEmpty = true;
        }
        else
        {
            isEmpty = false;
        }

        //recalculating all cells that depends on this cell
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

Tree* Cell::getTree()
{
    return tree;
}

const Tree* Cell::getTree() const
{
    return tree;
}


QString Cell::getValue() const
{

    return tree->getResult();
}

//convert cell reference formula to coordinate pair of coordinates [row, column]
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

    if(rowNum >  parent->rowCount() || columnNum >  parent->columnCount())
    {
        tree->calcExeption = true;
        return std::make_pair(-1,-1);
    }
    return std::make_pair(rowNum, columnNum);
}

QTableWidget* Cell::getParent()
{
    return parent;
}
