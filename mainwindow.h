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

private:

    void setIsModified(bool state);

private slots:

     void spreadsheetModified();
     void on_actionNew_triggered();
     void on_action_Open_triggered();
     void on_action_Save_triggered();
     void on_action_Exit_triggered();
     void on_action_Save_as_triggered();
     void on_action_Recalculate_triggered();
     void on_action_About_Qt_triggered();
     void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
