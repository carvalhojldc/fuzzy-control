#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QStringList>
#include "qcustomplot.h"
#include "connection.h"
#include "fuzzy.h"
#include "fuzzyConfigUI.h"
#include "signal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, protected Signal
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void connectServer();

    void UI_configGraphWrite();
    void UI_configGraphRead();
    void UI_DisplayGraph();

    void receiveData();
    void sendData();

    void configFuzzyFunction();


private:
    Ui::MainWindow *ui;

    Connection *connection;

    QTimer *timerWrite;
    QTimer *timerRead;

    QThread *threadWrite;
    QThread *threadRead;

    FuzzyControl *fuzzyControl;
    Fuzzy myFuzzy;
    FuzzyConfigUI fuzzyConfigUI;


};

#endif // MAINWINDOW_H
