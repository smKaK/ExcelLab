#include "cell.h"
#include "node.h"
#include "parser.h"
#include "lexer.h"
#include <QDebug>
#include"tree.h"

Cell::Cell(QTableWidget* parent)
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

QVariant Cell::getAnotherCellData(int row, int column) const
{
    qDebug() << row << " " << column;

    return parent->item(row-1,column-1)->data(Qt::DisplayRole);
}

QTableWidgetItem *Cell::clone() const
{
    return new Cell(*this);
}


//QVariant Cell::data(int role) const
//{

//        if(role ==Qt::DisplayRole)
//        {
//            QVariant res = this->getValue();
//            if( res.isValid()){
//                return res;

//            } else
//            {
//                 return QVariant("Wrong Input");
//            }
//        }
//        return QTableWidgetItem::data(role);

//}

void Cell::setData(int role, const QVariant &value)
{
    qDebug() << "set value " << value;
     tree->setHead( Parser::parse(Lexer::Tokenize(value.toString())));
     for(auto& el : Lexer::Tokenize(value.toString()))
     {
         qDebug() << el.GetLexema();
     }

    QTableWidgetItem::setData(Qt::DisplayRole, getValue());
    if (role == Qt::EditRole)
        setDirty();
}

QString Cell::getValue() const
{
    return tree->getResut();
}
