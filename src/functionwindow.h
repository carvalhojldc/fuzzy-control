#ifndef FUNCTIONWINDOW_H
#define FUNCTIONWINDOW_H

#include "qcustomplot.h"
#include <QDialog>
#include <QMessageBox>
#include <QList>
#include "fuzzy.h"

namespace Ui {
class FunctionWindow;
}

class FunctionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FunctionWindow(Fuzzy * fuzzy, QWidget *parent = 0);
    ~FunctionWindow();

private:
    //void configGraph(void);
    void clearGraph(int & id);
    void clearAllGraphs(void);
    void clearTable(void);
    void addGraph(const FuzzyFunction *function, const int &id);
    void addDataTable(const FuzzyFunction *function);

    FuzzyVariable * getIO(void);

    bool errorIO(void);

    void setCurrentFunction(const int id);
    void clearCurrentFunction();

    bool sugenoAndOut();

    bool isEdit;

private slots:
    void graphLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me);
    void graphClick(QCPAbstractPlottable *plottable, QMouseEvent *me);

    void changeCurrentIO(void);
    void changeIORange(void);

    void insertFunction(void);
    void deleteFunction(void);
    void deleteAllFunctions(void);
    void editFunction(void);

    void currentFunctionSugeno();


private:
    Ui::FunctionWindow *ui;
    Fuzzy *myFuzzy;
    FuzzyVariable *io;

    int currentFunction;
};

#endif // FUNCTIONWINDOW_H
