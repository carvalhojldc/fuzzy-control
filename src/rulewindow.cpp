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

    connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(currentRule(QTableWidgetItem*)));

    //ui->listWidget->setStyleSheet( "QListWidget::item { border-bottom: 1px solid black; }" );
    //ui->listWidget->setProperty("separator", true);

    //ui->removeRule->setDisabled(true);
    //ui->label_currentRule->setText("Nenhuma regra selecionada");
    //ui->label_numberRules->setText("0");

    QStringList HorizontalHeaderLabels = {"REGRAS"};
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(HorizontalHeaderLabels);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0, 680);

    // load rules
    int fuzyRules_size = myFuzzy->rules.size();
    if(fuzyRules_size != 0) {
        QList<FuzzyRule> tempListRule;
        FuzzyRule tempRule;
        QString rule;
        // QList<QList<FuzzyRule>> rules;

        for(int i=0; i<fuzyRules_size; i++) {
            tempListRule = myFuzzy->rules.at(i);

            for(int j=0; j<tempListRule.size(); j++) {
                if(j == 0)
                    rule = "SE ";
                else if(j == tempListRule.size()-1)
                    rule += " ENTÃO ";
                else
                    rule += " E ";

                tempRule = tempListRule.at(j);

                rule += ( " [ " + tempRule.io->name + " É " + \
                        tempRule.io->fuzzyFunctions.at( (tempRule.idFunction) ).name + " ] " );
            }

            ui->tableWidget->setRowCount( i+1 );
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem( rule ));
        }
    }
    ui->label_numberRules->setText( QString::number(fuzyRules_size) );
    // END load rules
    //---------------
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

    int idNewRule;
    QString rule = "";

    QList<FuzzyRule> newRules;
    FuzzyRule temp;

    if(myFuzzy->statusInputP) {
        rule = "SE [ " + myFuzzy->inputP.name + " É " + ui->comboBox_1->currentText() + " ] ";

        temp.io = &myFuzzy->inputP;
        temp.idFunction = ui->comboBox_1->currentIndex();
        newRules.push_back( temp );
    }

    if(myFuzzy->statusInputI) {
        rule += (" E [ " + myFuzzy->inputI.name + " É " + ui->comboBox_2->currentText() + " ] " );

        temp.io = &myFuzzy->inputI;
        temp.idFunction = ui->comboBox_2->currentIndex();
        newRules.push_back( temp );
    }

    if(myFuzzy->statusInputD) {
        rule += (" E [ " + myFuzzy->inputD.name + " É " + ui->comboBox_3->currentText() + " ] " );

        temp.io = &myFuzzy->inputD;
        temp.idFunction = ui->comboBox_3->currentIndex();
        newRules.push_back( temp );
    }

    // output
    rule += " ENTÃO [ " + myFuzzy->output.name + " É " + ui->comboBox_4->currentText() + " ] ";

    for(int r=0; r<ui->tableWidget->rowCount(); r++)
    {
        QString row = ui->tableWidget->item(r,0)->text();

        if(row == rule)
        {
            QMessageBox::critical(0, "Adicionar regra",
                              "A regra escolhida já foi inserida, insira outra diferente de:\n" + rule);
            return;
        }
    }

    temp.io = &myFuzzy->output;
    temp.idFunction = ui->comboBox_4->currentIndex();
    newRules.push_back( temp );

    // --

    myFuzzy->rules.push_back(newRules);

    idNewRule = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount( idNewRule + 1 );
    ui->tableWidget->setItem(idNewRule, 0, new QTableWidgetItem( rule ));

    ui->label_numberRules->setText( QString::number(idNewRule+1) );

    if(!ui->removeRule->isEnabled())
        ui->removeRule->setEnabled(true);
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
}


void RuleWindow::currentRule(QTableWidgetItem* item)
{
    ui->removeRule->setEnabled(true);
    ui->label_currentRule->setText( item->text() );
}
