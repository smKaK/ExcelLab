#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool bIsModified;
    QString curFile;

private:

    void setIsModified(bool state);
    bool okToContinue();
    bool saveFile(const QString& fileName);
    bool loadFile(const QString& fileName);
    void setCurFile(const QString& fileName);

private slots:
     void setFormulaInLineEdit(int row,int column);
     void spreadsheetModified();
     void on_actionNew_triggered();
     void on_action_Open_triggered();
     bool on_action_Save_triggered();
     void on_action_Exit_triggered();
     bool on_action_Save_as_triggered();
     void on_action_Recalculate_triggered();
     void on_action_About_Qt_triggered();
     void on_actionAbout_triggered();
     void on_actionAdd_Column_triggered();
     void on_actionAdd_Row_triggered();
     void on_actiondebug_triggered();

protected:

     void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
