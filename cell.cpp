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
    tree->recalculate();
    setData(Qt::DisplayRole, getValue());
}

QVariant Cell::getAnotherCellData(int row, int column) const
{
    qDebug() << row << " " << column;
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
        formula = value.toString();
        qDebug() << "set value " << value;
        //tree->setFormula(value.toString());
        auto tokens = Lexer::Tokenize(value.toString());

        for(const auto& el : tokens)
        {
            if(el.getType() == TokenType::kCell)
            {
                std::pair<int, int> coords = coordByLink(el.GetLexema());

               Cell* cell = static_cast<Cell*>(parent->item(coords.first, coords.second));
               if(cell == nullptr)
               {
                    Cell* newCell = new Cell(parent);
                    newCell->cellsThatRef.push_back(this);
                    parent->setItem(coords.first, coords.second, newCell);
               }
               else
               {
                    cell->cellsThatRef.push_back(this);
                }

            }
        }

    //    for(auto el : cellsThatRef)
    //    {
    //        qDebug() << "cells in formula " << el.first << " " << el.second;
    //    }

     //   tree->setHead( Parser::parse(tokens));

        tree->setHead(Parser::parse(tokens));

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
            //qDebug() << this->row() << " " << this->column();
            //qDebug() << el.first << " " << el.second;
            el->recalculate();
        }



        if (role == Qt::EditRole)
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
