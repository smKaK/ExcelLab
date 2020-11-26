#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "cell.h"
#include <QCloseEvent>

//Constructor and destructor/////////////////////////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    bIsModified(false)
{
    ui->setupUi(this);
    connect(ui->tableWidget, SIGNAL(modified()),
    this, SLOT(spreadsheetModified()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



//Spreadsheet Modified///////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::spreadsheetModified()
{
    qDebug() << "spreadsheet modified mainwindow";
    setIsModified(true);
  // updateStatusBar();
}

void MainWindow::setIsModified(bool state)
{
    bIsModified = state;
}

//okToContinue/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MainWindow::okToContinue()
{
    qDebug() << "Debug: okToContinue";
    if (bIsModified) {
    int r = QMessageBox::warning(this, tr("SpreadsheetM"),
    tr("The document has been modified.\n"
    "Do you want to save your changes?"),
    QMessageBox::Yes | QMessageBox::No|
    QMessageBox::Cancel);
    if (r == QMessageBox::Yes) {
    return on_action_Save_triggered();
    } else if (r == QMessageBox::Cancel) {
    return false;
    }
    }
    return true;

}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!ui->tableWidget->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
       }
    setCurFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;

}

void MainWindow::setCurFile(const QString &fileName)
{
    curFile = fileName;
}

//Slots/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void MainWindow::on_actionNew_triggered()
{
     qDebug() << "NewSlot";
}

void MainWindow::on_action_Open_triggered()
{
    if (okToContinue()){
        QString fileName = QFileDialog::getOpenFileName(this,
        tr("0pen Spreadsheet"),".",
        tr("Spreadsheet files (*.xml)"));

    if (!fileName.isEmpty())
         loadFile(fileName);

}
}

bool MainWindow::on_action_Save_triggered()
{
    qDebug() << "SaveSlot";
    if (curFile.isEmpty()) {
        return on_action_Save_as_triggered();
    } else {
        return saveFile(curFile);
    }

    return true;
}

void MainWindow::on_action_Exit_triggered()
{
     qDebug() << "ExitSlot";
}

bool MainWindow::on_action_Save_as_triggered()
{
    //qDebug() << "SaveAsSlot";
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Spreadsheet"), ".",
                               tr("Spreadsheet files (*.xml)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);

}

void MainWindow::on_action_Recalculate_triggered()
{
     qDebug() << "RecalculateSlot";
}

void MainWindow::on_action_About_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr ( "Про програму" ),
    tr( "<h2>Лабораторна \"Редактор таблиць\" 1.1</h2>"
        "<р>Кляцко Семен К-24"));
}

void MainWindow::on_actionAdd_Column_triggered()
{
    ui->tableWidget->addColumn();
}

void MainWindow::on_actionAdd_Row_triggered()
{
    ui->tableWidget->addRow();
}

//Save File/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MainWindow::saveFile(const QString &fileName)
{
    if (!ui->tableWidget->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    bIsModified = false;
    return true;
}

//Close Event///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(bIsModified)
    {
        if (okToContinue()) {
            event->accept();
         }  else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}




void MainWindow::on_actiondebug_triggered()
{
  qDebug() << static_cast<Cell*>(ui->tableWidget->item(1,1))->getAnotherCellData(2,2);
}
