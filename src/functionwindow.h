#ifndef FUNCTIONWINDOW_H
#define FUNCTIONWINDOW_H

#include "qcustomplot.h"
#include <QDialog>
#include <QMessageBox>

#include "fuzzy.h"

#include <QDebug>

namespace Ui {
class FunctionWindow;
}

class FunctionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FunctionWindow(QWidget *parent = 0);
    ~FunctionWindow();

private slots:
    void controlInput(int id);
    void currentInput();

    FuzzyVariable * getIO();

    void updateCurrentData(FuzzyVariable * io);

    void insertIORange(void);

    void insertFunction(void);
    void deleteFunction(void);
    void editFunction(void);

    void plotterLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me);

private:
    Ui::FunctionWindow *ui;
    Fuzzy myFuzzy;

};

#endif // FUNCTIONWINDOW_H
