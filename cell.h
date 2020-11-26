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

    int getColour() const;
    void setColour(int newColour);
    Tree* getTree();
    const Tree* getTree() const;
    QTableWidget *getParent();
    QVector<Cell *> getCellsThatRefs() const;
    QVector<Cell *>& getCellsThatRefs();
    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString getFormula() const;
    void setDirty();
    bool getIsEmpty() const;
    void recalculate();
    QVariant getAnotherCellData(int row, int column) const;

private:

    int colour;
    QTableWidget* parent;
    QVector<Cell*> cellsThatRef;
    QVector<Cell*> cellsINFormula;
    Tree* tree;
    QString formula;
    bool isEmpty;
    QString getValue() const ;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;
    std::pair<int,int> coordByLink(const QString& link) const;
};

#endif // CELL_H
