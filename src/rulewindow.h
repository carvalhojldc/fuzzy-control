#ifndef RULEWINDOW_H
#define RULEWINDOW_H

#include <QDialog>
#include "fuzzy.h"

namespace Ui {
class RuleWindow;
}

class RuleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RuleWindow(Fuzzy &fuzzy, QWidget *parent = 0);
    ~RuleWindow();

private:
    Ui::RuleWindow *ui;
    Fuzzy myFuzzy;
};

#endif // RULEWINDOW_H
