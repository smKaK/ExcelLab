#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>
#include <QObject>
#include "node.h"
#include <QStack>

class Spreadsheet : public QTableWidget
{
    Q_OBJECT

signals:
    void modified();
private:
    bool autoRecalc;
    QStack<Cell*> cycleStack;
    bool dfs(Cell* v);

public:
    Spreadsheet(QWidget* parent = nullptr);
    ~Spreadsheet();
    QString currentLocation();
    bool cycleDetector(Cell*);
    void clear();

public slots:
    void recalculate();
    void setAutoRecalculation(bool b);
    void SpreadsheetModified();
    void setHeaders();
    void addRow();
    void addColumn();
    void setHeader(int col);
    bool writeFile(const QString &fileName);
    bool readFile(const QString &fileName);

};

#endif // SPREADSHEET_H
