#ifndef RULEWINDOW_H
#define RULEWINDOW_H

#include <QDialog>

namespace Ui {
class RuleWindow;
}

class RuleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RuleWindow(QWidget *parent = 0);
    ~RuleWindow();

private:
    Ui::RuleWindow *ui;
};

#endif // RULEWINDOW_H
