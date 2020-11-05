#ifndef CELL_H
#define CELL_H
#include <QTableWidgetItem>
#include "token.h"

class Node_Statement;

class Cell : public QTableWidgetItem
{
public:
    Cell();
    ~Cell();
    QTableWidgetItem *clone() const;
    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString formula() const;
    void setDirty();
    QVariant getAnotherCellData(int row, int column) const;
private:
    QSharedPointer<Node_Statement> s;
    QString val;
    QString getValue() const ;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;

};

#endif // CELL_H
