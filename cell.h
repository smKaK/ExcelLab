#ifndef CELL_H
#define CELL_H
#include <QTableWidgetItem>
#include "token.h"
#include "spreadsheet.h"

class Tree;
class Node_Statement;

class Cell : public QTableWidgetItem
{
public:
    Cell(QTableWidget* parent);
    ~Cell();
    QTableWidgetItem *clone() const;

    void setData(int role, const QVariant &value);
    //QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString formula() const;
    void setDirty();
    QVariant getAnotherCellData(int row, int column) const;
private:
    QTableWidget* parent;
    Tree* tree;
    QSharedPointer<Node_Statement> s;
    QString val;
    QString getValue() const ;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;

};

#endif // CELL_H
