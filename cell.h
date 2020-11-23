#ifndef CELL_H
#define CELL_H
#include <QTableWidgetItem>
#include "token.h"
#include "spreadsheet.h"
#include <QObject>

class Tree;
class Node_Statement;

class Cell : public QTableWidgetItem
{

public:
    Cell(QTableWidget* parent);
    ~Cell();
    QTableWidgetItem *clone() const;

    void setData(int role, const QVariant &value);
   QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString getFormula() const;

    void setDirty();
    bool getIsEmpty() const;
    void recalculate();
    QVariant getAnotherCellData(int row, int column) const;

    QTableWidget *getParent();
    QVector<Cell*> cellsThatRef;
    Tree* tree;
private:
    //vector<>

    QTableWidget* parent;

    //QSharedPointer<Node_Statement> s;
    QString formula;
    bool isEmpty;
    QString getValue() const ;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;
    std::pair<int,int> coordByLink(const QString& link) const;
};

#endif // CELL_H
