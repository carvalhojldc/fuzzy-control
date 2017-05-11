#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QStringList>

#include "qcustomplot.h"

#include "fuzzycontrol.h"

#include "functionwindow.h"
#include "rulewindow.h"

#include "signal.h"
#include "connection.h"
#include "fuzzy.h"

#include <QDebug>

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

    void UI_functionWindow();
    void UI_ruleWindow();

    void controlInput(int id);

    double carrierSignal(double voltage);

    void myFuzzyControl();
    void myGraph();

    void UI_limitRandInput();
    void UI_configSignal(int signal);

    void updateData();

    void MandSugStatus();
private:
    Ui::MainWindow *ui;
    FunctionWindow *ui_fw;
    RuleWindow *ui_rw;

    Connection *connection;

    Signal signal;

    Fuzzy myFuzzy;

    FuzzyControl fuzzyControl;

    QTimer *timerFuzzyControl;
    QTimer *timerGraph;

    QThread *threadFuzzyControl;
    QThread *threadGraph;

    const QVector<QString> graphRead      = { "Erro", "Set Point", "Tanque 1", "Tanque 2" };
    const QVector<QString> graphReadColor = { "red",  "black",     "blue",     "green" };

    const QVector<QString> graphWrite      = {"Sinal Enviado", "Sinal Calculado"};
    const QVector<QString> graphWriteColor = { "blue",         "red" };

    double timeAux;
    int    signalID;
    double setPoint;
    double offSet;
    double period;
    double periodMax;

    int channelWrite = -1;
    bool readLeavel1 = false;
    bool readLeavel2 = false;

    double calculatedSignal = 0;
    double sendSignal = 0;
    double error = 0;

    double tankLevel_1;
    double tankLevel_2;
    double fuzzySignal = 0;

    bool stopWrite = false;
};

#endif // MAINWINDOW_H
