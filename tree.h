#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "cell.h"

class Tree
{
public:
    Tree(Cell* parentCell, QSharedPointer<Node_Statement> head = nullptr);
    void setHead(QSharedPointer<Node_Statement> newHead);
    QSharedPointer<Node_Statement> getHead() const;
    QString getResut() const;
private:
    QSharedPointer<Node_Statement> head;
    QString result;
    Cell* parentCell;
    void calculate();

};

#endif // TREE_H
