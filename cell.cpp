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

QVariant Cell::getAnotherCellData(int row, int column) const
{
    qDebug() << row << " " << column;

    return parent->item(row-1,column-1)->data(Qt::DisplayRole);

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
    qDebug() << "set value " << value;
    //tree->setFormula(value.toString());

    tree->setHead( Parser::parse(Lexer::Tokenize(value.toString())));

    QTableWidgetItem::setData(role, value);



    if(this->data(Qt::DisplayRole) == "")
    {
        isEmpty = true;
    }
    else
    {
        isEmpty = false;
    }

    if (role == Qt::EditRole)
        setDirty();
}

void Cell::setFormula(const QString &formula)
{
     setData(Qt::EditRole, formula);

}

QString Cell::getFormula() const
{
   return data(Qt::EditRole).toString();
}

QString Cell::getValue() const
{
    return tree->getResult();
}

QTableWidget* Cell::getParent()
{
    return parent;
}
