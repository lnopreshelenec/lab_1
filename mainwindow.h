#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Keeper.h"
#include "speaker.h"
#include "admin.h"
#include "programm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addSpeaker_clicked();
    void on_addAdmin_clicked();
    void on_addProgram_clicked();
    void on_removeItem_clicked();
    void on_saveToFile_clicked();
    void on_loadFromFile_clicked();
    void on_clearAll_clicked();
    void updateDisplay();

private:
    Ui::MainWindow *ui;
    Keeper keeper;

    void displaySpeakers();
    void displayAdmins();
    void displayPrograms();
    void displayAll();
};

#endif  // MAINWINDOW_H
