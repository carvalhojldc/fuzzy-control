#include "rulewindow.h"
#include "ui_rulewindow.h"

RuleWindow::RuleWindow(Fuzzy * fuzzy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleWindow)
{
    myFuzzy = fuzzy;

    ui->setupUi(this);

    if(myFuzzy->statusInputP) {
        FuzzyVariable *var = &myFuzzy->inputP;
        ui->label_1->setText( var->name );

        for(int i=0; i<var->fuzzyFunctions.size(); i++)
             ui->comboBox_1->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));

        ui->widget->setVisible(true);
    } else
        ui->widget->setVisible(false);

    if(myFuzzy->statusInputI) {
        FuzzyVariable *var = &myFuzzy->inputI;
        ui->label_2->setText( var->name );

        for(int i=0; i<var->fuzzyFunctions.size(); i++)
             ui->comboBox_2->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));

        ui->widget_2->setVisible(true);
    } else
        ui->widget_2->setVisible(false);

    if(myFuzzy->statusInputD) {
        FuzzyVariable *var = &myFuzzy->inputD;
        ui->label_3->setText( var->name );

        for(int i=0; i<var->fuzzyFunctions.size(); i++)
             ui->comboBox_3->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));

        ui->widget_3->setVisible(true);
    } else
        ui->widget_3->setVisible(false);

    FuzzyVariable *var = &myFuzzy->output;
    ui->label_4->setText( var->name );

    for(int i=0; i<var->fuzzyFunctions.size(); i++)
         ui->comboBox_4->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));
    ui->widget_4->setVisible(true);

    connect(ui->insertRule, SIGNAL(clicked(bool)), this, SLOT(insertRule()));
    connect(ui->removeRule, SIGNAL(clicked(bool)), this, SLOT(removeRule()));

    //ui->listWidget->setStyleSheet( "QListWidget::item { border-bottom: 1px solid black; }" );
    ui->listWidget->setProperty("separator", true);
}

RuleWindow::~RuleWindow()
{
    delete ui;
}

void RuleWindow::insertRule()
{
    if( (myFuzzy->statusInputP && myFuzzy->inputP.fuzzyFunctions.size() == 0) ||
        (myFuzzy->statusInputI && myFuzzy->inputI.fuzzyFunctions.size() == 0) ||
        (myFuzzy->statusInputD && myFuzzy->inputD.fuzzyFunctions.size() == 0) ||
        (myFuzzy->output.fuzzyFunctions.size() == 0)
            )
    {
        QMessageBox::critical(0, "Adicionar regra", "Configuração inválida, adicione funções de pertinência nas IO em vazio!");
        return;
    }

    int idNewRule = ui->listWidget->size().height();
    QString rule = "";

    if(myFuzzy->statusInputP)
        rule = "SE [ " + myFuzzy->inputP.name + " É " + ui->comboBox_1->currentText() + " ] ";

    if(myFuzzy->statusInputI)
        rule += (" E [ " + myFuzzy->inputI.name + " É " + ui->comboBox_2->currentText() + " ] " );

    if(myFuzzy->statusInputD)
        rule += (" E [ " + myFuzzy->inputD.name + " É " + ui->comboBox_3->currentText() + " ] " );

    // output
    rule += " ENTÃO [ " + myFuzzy->output.name + " É " + ui->comboBox_4->currentText() + " ] ";

    ui->listWidget->insertItem(idNewRule, rule);
}

void RuleWindow::removeRule()
{
    int currentId = ui->listWidget->currentIndex().row();
    ui->listWidget->model()->removeRow( currentId );
}
