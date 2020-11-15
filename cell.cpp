#include "cell.h"
#include "node.h"
#include "parser.h"
#include "lexer.h"
#include <QDebug>

Cell::Cell()
{
    setDirty();


}

Cell::~Cell()
{

}


void Cell::setDirty()
{
    cacheIsDirty = true;
}

QVariant Cell::getAnotherCellData(int row, int column) const
{
    return this->tableWidget()->item(row, column)->text();
}

QTableWidgetItem *Cell::clone() const
{
    return new Cell(*this);
}

QVariant Cell::data(int role) const
{

        if(role ==Qt::DisplayRole)
        {
            QVariant res = this->getValue();
            if( res.isValid()){
                return res;

            } else {
                 return QVariant("Wrong Input");
                 }
        }
        return QTableWidgetItem::data(role);

}

void Cell::setData(int role, const QVariant &value)
{
    qDebug() << "set value " << value;
     s = Parser::parse(Lexer::Tokenize("4+8"));
     val = s->calculate(this).str().data();
     for(auto& el : Lexer::Tokenize("2*a"))
     {
         qDebug() << el.GetLexema();
     }
     //getValue();
    QTableWidgetItem::setData(role, value);


    if (role == Qt::EditRole)
        setDirty();
}

QString Cell::getValue() const
{
    qDebug() << "GetValue" << this->row() << ' ' << this->column();
    return val;
}
