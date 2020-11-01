#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

//Constructor and destructor/////////////////////////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    setWindowModified(true);
  // updateStatusBar();
}

void MainWindow::setIsModified(bool state)
{
    bIsModified = state;
}



//bool MainWindow::okToContinue()
//{
//    qDebug() << "Debug: okToContinue";
//    if (bIsModified) {
//    int r = QMessageBox::warning(this, tr("SpreadsheetM"),
//    tr("The document has been modified.\n"
//    "Do you want to save your changes?"),
//    QMessageBox::Yes | QMessageBox::No|
//    QMessageBox::Cancel);
//    if (r == QMessageBox::Yes) {
//    return on_action_Save_triggered();
//    } else if (r == QMessageBox::Cancel) {
//    return false;
//    }
//    }
//    return true;

//}

//Slots/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_action_Open_triggered()
{

}

void MainWindow::on_action_Save_triggered()
{

}

void MainWindow::on_action_Exit_triggered()
{

}

void MainWindow::on_action_Save_as_triggered()
{

}

void MainWindow::on_action_Recalculate_triggered()
{

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
