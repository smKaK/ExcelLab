#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>
#include <QObject>

class Spreadsheet : public QTableWidget
{
    Q_OBJECT

signals:
    void modified();
private:
    bool autoRecalc;



public:
    Spreadsheet(QWidget* parent = nullptr);
    ~Spreadsheet();
    QString currentLocation();

    void clear();

public slots:
    void recalculate();
    void setAutoRecalculation(bool b);
    void SpreadsheetModified();

    void setHeaders();
        void addRow();
        void addColumn();
  void setHeader(int col);


};

#endif // SPREADSHEET_H
