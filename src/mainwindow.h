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

    void UI_configGraphs();
    //void UI_configGraphRead();

    void UI_DisplayGraph();

    void UI_functionWindow();
    void UI_ruleWindow();

    void controlInput(int id);

    double carrierSignal(double voltage);

    double travel(double calculatedSignal, double tankLevel_2);
    void myFuzzyControl();
    void myGraph();

    void UI_limitRandInput();
    void UI_configSignal(int signal);

    void updateData();

    void MandSugStatus();

private:
    Ui::MainWindow *ui;
    FunctionWindow *ui_function;
    RuleWindow     *ui_rule;
    Connection     *connection;
    Signal         signal;
    Fuzzy          myFuzzy;
    FuzzyControl   fuzzyControl;

   // QTimer *timerFuzzyControl;
   // QTimer *timerGraph;

    QThread *threadFuzzyControl;
    QThread *threadGraph;

    const QVector<QString> graphRead       = { "Erro", "Set Point", "Tanque 1", "Tanque 2" };
    const QVector<QString> graphReadColor  = { "red",  "black",     "blue",     "green" };
    const QVector<QString> graphWrite      = { "Sinal Enviado", "Sinal Calculado"};
    const QVector<QString> graphWriteColor = { "blue",          "red" };

    double timeAux   = 0;
    int    signalID  = 0;
    double setPoint  = 0;
    double offSet    = 0;
    double period    = 0;
    double periodMax = 0;

    int channelWrite = 0;
    bool readLeavel1 = true;
    bool readLeavel2 = true;
    bool isWrite     = false;

    double calculatedSignal = 0.0;
    double sendSignal       = 0.0;
//    double sendSignal_temp = 0;
    double error            = 0.0;
    double tankLevel_1      = 0.0;
    double tankLevel_2      = 0.0;
    double fuzzySignal      = 0.0;

//    bool stopWrite = false;

    /* in ms */
    const int timerSleep = 90;
};

#endif // MAINWINDOW_H
