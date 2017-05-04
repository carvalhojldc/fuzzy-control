#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QStringList>

#include "qcustomplot.h"

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

    void myFuzzyControl();
    void myGraph();

    void UI_limitRandInput();
    void UI_configSignal(int signal);

private:
    Ui::MainWindow *ui;
    FunctionWindow *ui_fw;
    RuleWindow *ui_rw;

    Connection *connection;

    Fuzzy myFuzzy;

    QTimer *timerFuzzyControl;
    QTimer *timerGraph;

    QThread *threadFuzzyControl;
    QThread *threadGraph;

    const QVector<QString> graphRead      = { "Erro", "Set Point", "Tanque 1", "Tanque 2" };
    const QVector<QString> graphReadColor = { "red",  "black",     "blue",     "green" };

    const QVector<QString> graphWrite      = {"Sinal Enviado", "Sinal Calculado"};
    const QVector<QString> graphWriteColor = { "blue",         "red" };

};

#endif // MAINWINDOW_H
