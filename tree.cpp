#include "tree.h"
#include "parser.h"
#include "lexer.h"

Tree::Tree(Cell *parentCell, QSharedPointer<Node_Statement> head) : parentCell(parentCell), head(head)
{
    calcExeption = false;
    calculate();
}

void Tree::setHead(QSharedPointer<Node_Statement> newHead)
{
    this->head = newHead;
    calculate();
}

QSharedPointer<Node_Statement> Tree::getHead() const
{
    return head;
}

QString Tree::getResult() const
{
    return result;
}

void Tree::setResult(const QString &newResult)
{
    result = newResult;
}

QString Tree::getFormula() const
{
    return formula;
}

void Tree::recalculate()
{
    calcExeption = false;
    calculate();
}

void Tree::setFormula(const QString &newFormula)
{
    formula = newFormula;
    setHead( Parser::parse(Lexer::Tokenize( formula)));
}

void Tree::calculate()
{
    calcExeption = false;
    if( head == nullptr ||( head->getExpressionNode() == nullptr && head->bIsExeption == false))
    {
        result = QString("");
    }
    else if (head->bIsExeption == true)
    {
        result = QString("####");
     }
    else
    {
        bool isEmptyCell = false;
        for(const auto& el : head->getCellLinks())
        {
            QString column;
            QString row;
            for(int i =0 ; i < el.GetLexema().length(); ++i)
            {
                if(el.GetLexema()[i].unicode() >= QChar('A').unicode() && el.GetLexema()[i].unicode() <= QChar('Z').unicode())
                {
                   column.push_back(el.GetLexema()[i]);
                } else {
                   row.push_back(el.GetLexema()[i]);
                }
            }
            int rowNum = row.toInt();
            int columnNum = 0;
            for(int i = column.length()-1; i >= 0; --i)
            {
                columnNum += std::pow(26, column.length() - 1 - i)*(column[i].unicode() - QChar('A').unicode() + 1);
            }

            if(!parentCell->getParent()->item(rowNum-1,columnNum-1))
            {
                isEmptyCell = true;
                break;
            }
        }
        if(isEmptyCell)
        {
            result = QString("####");
        }
        else {
             result = head->calculate(parentCell).str().data();
             if(calcExeption)
             {
                 result = QString("####");
             }
        }

    }
}
