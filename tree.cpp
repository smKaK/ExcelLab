#include "tree.h"

Tree::Tree(Cell *parentCell, QSharedPointer<Node_Statement> head) : parentCell(parentCell), head(head)
{
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

QString Tree::getResut() const
{
    return result;
}

void Tree::calculate()
{

    if(head == nullptr)
    {
        result = QString("empty");
    }
    else if (head->bIsExeption == true)
    {
        result = QString("####");
     }
    else
    {
         result = head->calculate(parentCell).str().data();
    }
}
