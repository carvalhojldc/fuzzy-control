#ifndef FUZZYUI_H
#define FUZZYUI_H

#include <QDialog>
#include <QMessageBox>

#include "fuzzy.h"

#include <QDebug>

namespace Ui {
class FuzzyConfigUI;
}

class FuzzyConfigUI : public QDialog
{
    Q_OBJECT

public:
    explicit FuzzyConfigUI(QWidget *parent = 0);
    ~FuzzyConfigUI();

private slots:
    void controlInput(int id);
    void currentInput();

    void insertFunction(void);
    FuzzyVariable *getIO();
    void updateCurrentData(FuzzyVariable *io);

private:
    Ui::FuzzyConfigUI *ui;
    Fuzzy myFuzzy;


};

#endif // FUZZYUI_H
