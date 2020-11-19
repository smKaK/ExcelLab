#include "spreadsheet.h"
#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTableWidget>
#include "cell.h"
#include <QXmlStreamWriter>

//Constructor and Destructor///////////////////////////////////////////////////////////////////////////////////////////////////

Spreadsheet::Spreadsheet(QWidget* parent)
{

    autoRecalc = true;

    setSelectionMode(ContiguousSelection);
    setItemPrototype(new Cell(this));

    clear();

    for(int i = 0; i < 10; ++i)
    {
        addRow();
        addColumn();
    }


    setHeaders();
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(SpreadsheetModified()));
}

Spreadsheet::~Spreadsheet()
{

}

//Column's headers/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Spreadsheet::setHeaders()
{
    for(int i = 0; i < columnCount(); ++i)
    {
        setHeader(i);
    }
}

void Spreadsheet::addRow()
{
    QTableWidget::insertRow(rowCount());
}

void Spreadsheet::addColumn()
{
    QTableWidget::insertColumn(columnCount());
    setHeader(columnCount()-1);
}


void Spreadsheet::setHeader(int col)
{
    if(col == 0)
    {
        QTableWidgetItem* itm = new QTableWidgetItem("A");
        setHorizontalHeaderItem(0, itm);
    } else {
        auto mod = model();
        QString prevHead = mod->headerData(col-1,Qt::Orientation::Horizontal).toString();
        bool allZ = true;
        for(int i = prevHead.length()-1; i >=0; --i)
        {
            if(prevHead[i] != 'Z')
            {
               prevHead[i] = QChar(prevHead[i].unicode() + 1);
               allZ = false;
               break;
            } else
            {
                prevHead[i] = 'A';
            }
        }
        if(allZ)
        {
            QTableWidgetItem* item = new QTableWidgetItem( QString(prevHead.length()+1, 'A'));
              setHorizontalHeaderItem(col, item);
        } else {

            QTableWidgetItem* item = new QTableWidgetItem(prevHead);
              setHorizontalHeaderItem(col, item);

         }
    }
}

bool Spreadsheet::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Spreadsheet" ),
                               tr("Cannot write file %1:\n%2." )
        .arg(file.fileName())
        .arg(file.errorString()));

        return false;
    }



    QXmlStreamWriter stream(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("table");

        stream.writeStartElement("preoperties");
            stream.writeTextElement("row_count", QString::number(this->rowCount()));
            stream.writeTextElement("Column_count", QString::number(this->columnCount()));
        stream.writeEndElement();   //properties
        stream.writeStartElement("cells");

        for(int i =0; i < this->rowCount(); ++i)
        {
            for(int j =0; j < this->columnCount(); ++j)
            {
                Cell* cell = static_cast<Cell*>(this->item(i,j));
                if( cell != nullptr)
                {
                    if(!cell->getIsEmpty())
                    {
                        stream.writeStartElement("cell");
                            stream.writeTextElement("row", QString::number(i));
                            stream.writeTextElement("column", QString::number(j));
                            stream.writeTextElement("formula", cell->data(Qt::EditRole).toString());
                        stream.writeEndElement();

                    }

                }

            }
        }
        stream.writeEndElement(); //cells
    stream.writeEndElement();   //table
    stream.writeEndDocument();

    QApplication:: restoreOverrideCursor();
    return true;
}


//Modifying and recalculation//////////////////////////////////////////////////////////////////////////////////////////////////

void Spreadsheet::recalculate()
{
    qDebug() << "Recalculate" << endl;

}

void Spreadsheet::setAutoRecalculation(bool b)
{
    autoRecalc = b;
    if (autoRecalc)
        recalculate();
}

void Spreadsheet::SpreadsheetModified()
{
    qDebug() << "SpredsheetModified spreadsheet";
    if(autoRecalc)
        recalculate();
    emit modified();
}

//Current Location//////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString Spreadsheet::currentLocation()
{

    return QString::number(currentColumn()+1)
           + QString::number(currentRow() + 1);

}

//Clear/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Spreadsheet::clear()
{
    setRowCount(0);
    setColumnCount(0);
    setCurrentCell(0, 0);
}






