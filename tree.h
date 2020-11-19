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
    QString getResult() const;
    QString getFormula() const;
    void setFormula(const QString& newFormula);
private:
    QSharedPointer<Node_Statement> head;
    QString result;
    QString formula;
    Cell* parentCell;
    void calculate();

};

#endif // TREE_H
