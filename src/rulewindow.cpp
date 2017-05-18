#include "rulewindow.h"
#include "ui_rulewindow.h"

RuleWindow::RuleWindow(Fuzzy * fuzzy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RuleWindow)
{
    myFuzzy = fuzzy;

    ui->setupUi(this);

    // config IO
    if(myFuzzy->statusError) {
        FuzzyVariable *var = &myFuzzy->error;
        ui->label_1->setText( var->name );

        for(int i=0; i<var->fuzzyFunctions.size(); i++)
             ui->comboBox_1->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));

        ui->widget->setVisible(true);
    } else
        ui->widget->setVisible(false);

    if(myFuzzy->statusErrorFiDerivative) {
        FuzzyVariable *var = &myFuzzy->errorFirstDerivative;
        ui->label_2->setText( var->name );

        for(int i=0; i<var->fuzzyFunctions.size(); i++)
             ui->comboBox_2->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));

        ui->widget_2->setVisible(true);
    } else
        ui->widget_2->setVisible(false);

    if(myFuzzy->statusErrorSeDerivative) {
        FuzzyVariable *var = &myFuzzy->errorSecondDerivative;
        ui->label_3->setText( var->name );

        for(int i=0; i<var->fuzzyFunctions.size(); i++)
             ui->comboBox_3->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));

        ui->widget_3->setVisible(true);
    } else
        ui->widget_3->setVisible(false);
    // END config IO
    // -------------

    FuzzyVariable *var = &myFuzzy->output;
    ui->label_4->setText( var->name );

    for(int i=0; i<var->fuzzyFunctions.size(); i++)
         ui->comboBox_4->addItem(var->fuzzyFunctions.at(i).name, QVariant(i));
    ui->widget_4->setVisible(true);

    connect(ui->insertRule, SIGNAL(clicked(bool)), this, SLOT(insertRule()));
    connect(ui->removeRule, SIGNAL(clicked(bool)), this, SLOT(removeRule()));

    connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(currentRule(QTableWidgetItem*)));

    // config table
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setMaximumWidth( ui->tableWidget->size().width() );

    // load rules
    int fuzyRules_size = myFuzzy->rules.size();
    if(fuzyRules_size != 0) {
        QList<FuzzyRule> tempListRule;
        FuzzyRule tempRule;
        QString rule;
        // QList<QList<FuzzyRule>> rules;

        for(int i=0; i<fuzyRules_size; i++) {
            tempListRule = myFuzzy->rules.at(i);

            for(int j=0; j<tempListRule.size(); j++)
            {
                tempRule = tempListRule.at(j);

                if(j == 0)
                    rule = "SE ";
                else if(j == tempListRule.size()-1)
                    rule += " ENTÃO ";
                else
                    rule += " E ";

                rule += ( " [ " + tempRule.io->name + " É " + \
                        tempRule.io->fuzzyFunctions.at( tempRule.idFunction ).name + " ] " );
            }

            ui->tableWidget->setRowCount( i+1 );
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem( rule ));
            ui->tableWidget->resizeColumnsToContents();
        }
    }
    ui->label_numberRules->setText( QString::number(fuzyRules_size) );
    // END load rules
    //---------------

    ui->removeRule->setEnabled(true);
}

RuleWindow::~RuleWindow()
{
    delete ui;
}

void RuleWindow::insertRule()
{
    if( (myFuzzy->statusError && myFuzzy->error.fuzzyFunctions.size() == 0) ||
        (myFuzzy->statusErrorFiDerivative && myFuzzy->errorFirstDerivative.fuzzyFunctions.size() == 0) ||
        (myFuzzy->statusErrorSeDerivative && myFuzzy->errorSecondDerivative.fuzzyFunctions.size() == 0) ||
        (myFuzzy->output.fuzzyFunctions.size() == 0)
            )
    {
        QMessageBox::critical(0, "Adicionar regra", "Configuração inválida! Defina funções para as entradas e saída!");
        return;
    }

    int idNewRule;
    QString rule = "";

    QList<FuzzyRule> newRules;
    FuzzyRule temp;

    if(myFuzzy->statusError) {
        rule = "SE [ " + myFuzzy->error.name + " É " + ui->comboBox_1->currentText() + " ] ";

        temp.io = &myFuzzy->error;
        temp.idFunction = ui->comboBox_1->currentIndex();
    }

    if(myFuzzy->statusErrorFiDerivative) {
        temp.operation = RULE_AND;
        newRules.push_back( temp );

        rule += (" E [ " + myFuzzy->errorFirstDerivative.name + " É " + ui->comboBox_2->currentText() + " ] " );

        temp.io = &myFuzzy->errorFirstDerivative;
        temp.idFunction = ui->comboBox_2->currentIndex();
    }

    if(myFuzzy->statusErrorSeDerivative) {
        temp.operation = RULE_AND;
        newRules.push_back( temp );

        rule += (" E [ " + myFuzzy->errorSecondDerivative.name + " É " + ui->comboBox_3->currentText() + " ] " );

        temp.io = &myFuzzy->errorSecondDerivative;
        temp.idFunction = ui->comboBox_3->currentIndex();
    }

    temp.operation = RULE_THEN;
    newRules.push_back( temp );

    // output
    rule += " ENTÃO [ " + myFuzzy->output.name + " É " + ui->comboBox_4->currentText() + " ] ";

    for(int r=0; r<ui->tableWidget->rowCount(); r++)
    {
        QString row = ui->tableWidget->item(r,0)->text();

        if(row == rule)
        {
            QMessageBox::critical(0, "Adicionar regra",
                    "Regrá já inserida, defina outra!");
            return;
        }
    }

    temp.io = &myFuzzy->output;
    temp.operation = RULE_END;
    temp.idFunction = ui->comboBox_4->currentIndex();
    newRules.push_back( temp );

    // --

    myFuzzy->rules.push_back(newRules);

    idNewRule = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount( idNewRule + 1 );
    ui->tableWidget->setItem(idNewRule, 0, new QTableWidgetItem( rule ));
    ui->tableWidget->resizeColumnsToContents();

    ui->label_numberRules->setText( QString::number(idNewRule+1) );
}

void RuleWindow::removeRule()
{
    int id = ui->tableWidget->currentRow();

    ui->tableWidget->removeRow( id );
    myFuzzy->rules.removeAt(id);

    int numberRules = ui->label_numberRules->text().toInt()-1;

    ui->label_numberRules->setText( QString::number( numberRules ) );

    ui->label_currentRule->setText("Nenhuma regra selecionada");
    ui->removeRule->setEnabled(false);
    ui->removeRule->setStyleSheet("background-color: none");
}


void RuleWindow::currentRule(QTableWidgetItem* item)
{
    ui->removeRule->setEnabled(true);
    ui->removeRule->setStyleSheet("background-color: red");
    ui->label_currentRule->setText( item->text() );
}
