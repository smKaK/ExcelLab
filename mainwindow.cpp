#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
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

//Slots/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void MainWindow::on_actionNew_triggered()
{
     qDebug() << "NewSlot";
}

void MainWindow::on_action_Open_triggered()
{
     qDebug() << "SaveOpenSlot";
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
    qDebug() << "SaveAsSlot";
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Spreadsheet"), ".",
                               tr("Spreadsheet files (*.sp)"));
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
        "<р>Кляцко Семен К-14"));
}

//Save File/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MainWindow::saveFile(const QString &fileName)
{
    qDebug() << "SaveFileMethod";
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

