#include "rulewindow.h"
#include "ui_rulewindow.h"

RuleWindow::RuleWindow(Fuzzy &fuzzy, QWidget *parent) :
    QDialog(parent),
    myFuzzy(fuzzy),
    ui(new Ui::RuleWindow)
{
    ui->setupUi(this);
}

RuleWindow::~RuleWindow()
{
    delete ui;
}
