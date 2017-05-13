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
    void configGraph(void);
    void clearGraph(int & id);
    void clearAllGraphs();
    void addGraph(const FuzzyFunction *function, const int &id);

    FuzzyVariable * getIO(void);

    bool ioError(void);

    void updateCurrentData(void);

private slots:
    void graphLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me);
    bool sugenoOUT();
    void changeCurrentIO(void);
    void changeIORange(void);

    void insertFunction(void);
    void deleteFunction(void);
    void editFunction(void);


private:
    Ui::FunctionWindow *ui;
    Fuzzy *myFuzzy;
    FuzzyVariable *io;
};

#endif // FUNCTIONWINDOW_H
