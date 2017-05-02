#include "fuzzyConfigUI.h"
#include "ui_fuzzyConfig.h"

FuzzyConfigUI::FuzzyConfigUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuzzyConfigUI)
{
    ui->setupUi(this);

    connect(ui->cb_controlFuzzy, SIGNAL(currentIndexChanged(int)), this, SLOT(controlInput(int)));

    connect(ui->rb_inputP, SIGNAL(clicked(bool)), this, SLOT(currentInput()));
    connect(ui->rb_inputI, SIGNAL(clicked(bool)), this, SLOT(currentInput()));
    connect(ui->rb_inputD, SIGNAL(clicked(bool)), this, SLOT(currentInput()));
    connect(ui->rb_output, SIGNAL(clicked(bool)), this, SLOT(currentInput()));

    connect(ui->pb_insertFunction, SIGNAL(clicked(bool)), this, SLOT(insertFunction()));

    //ui->funcionPlot->addGraph();
    ui->funcionPlot->xAxis->setLabel("x");
    ui->funcionPlot->yAxis->setLabel("y");

    for(int i=0; i<myFuzzy.controlFuzzy.size(); i++)
        ui->cb_controlFuzzy->addItem(myFuzzy.controlFuzzy.at(i), QVariant(i));

    for(int i=0; i<myFuzzy.nameFuzzyFunctions.size(); i++)
        ui->cb_InsertFunctionType->addItem(myFuzzy.nameFuzzyFunctions.at(i), QVariant(i));
}

FuzzyConfigUI::~FuzzyConfigUI()
{
    delete ui;
}

void readIO(FuzzyVariable &io, QRadioButton &rb)
{
    io.name = rb.text();
    //io.range = rb.
}

void FuzzyConfigUI::controlInput(int id)
{
    if(id == 0) { // fuzzy p
        ui->rb_inputP->setHidden(false);
        ui->rb_inputI->setHidden(true);
        ui->rb_inputD->setHidden(true);
    }
    else if(id == 1) { // fuzzy pi
        ui->rb_inputP->setHidden(false);
        ui->rb_inputI->setHidden(false);
        ui->rb_inputD->setHidden(true);
    }
    else if(id == 2) { // fuzzy pd
        ui->rb_inputP->setHidden(false);
        ui->rb_inputI->setHidden(true);
        ui->rb_inputD->setHidden(false);
    }
    else if(id == 3) { // fuzzy pid
        ui->rb_inputP->setHidden(false);
        ui->rb_inputI->setHidden(false);
        ui->rb_inputD->setHidden(false);
    }
}

void FuzzyConfigUI::currentInput() {
    FuzzyVariable *io;

    ui->lb_fuzzyIO->setText( "Entrada" );

    if(ui->rb_inputP->isChecked()) {
        io = &myFuzzy.inputP;
    }
    else if(ui->rb_inputI->isChecked()) {
        io = &myFuzzy.inputI;
    }
    else if(ui->rb_inputD->isChecked()) {
        io = &myFuzzy.inputD;
    }
    else { // ui->rb_output->isChecked()

        io = &myFuzzy.output;
        ui->lb_fuzzyIO->setText( "Saída" );
    }

    ui->lb_fuzzyVari->setText( io->name );
    ui->le_fuzzyRange->setText( io->range );
}

void FuzzyConfigUI::insertFunction()
{
    if(ui->le_InsertFunctionName->text().isEmpty()) {
        QMessageBox::critical(0,
                              "Inserir função",
                              "Nome inválido!");
    } else if(ui->le_InsertRangeFunction->text().isEmpty()) {
        QMessageBox::critical(0,
                              "Inserir função",
                              "Intervalo inválido!");
    } else {
        FuzzyFunction newFunction;
        FuzzyVariable *io = getIO();

        if(io == nullptr) return;

        /*

            TODO

            verificaçao de range
        */

        newFunction.type  = ui->cb_InsertFunctionType->currentIndex();
        newFunction.name  = ui->le_InsertFunctionName->text();
        newFunction.range = ui->le_InsertRangeFunction->text();

            /*
                TODO

                verificar se eh mad ou sugeno
            */


        io->fuzzyFunctions.push_back(newFunction);
        updateCurrentData(io);
    }


}

FuzzyVariable* FuzzyConfigUI::getIO()
{
    if(ui->rb_inputP->isChecked()) {
        return &myFuzzy.inputP;
    }
    else if(ui->rb_inputI->isChecked()) {
        return &myFuzzy.inputI;
    }
    else if(ui->rb_inputD->isChecked()) {
        return &myFuzzy.inputD;
    }
    else if(ui->rb_output->isChecked()) {
        return &myFuzzy.output;
    } else
        return nullptr;
}

void FuzzyConfigUI::updateCurrentData(FuzzyVariable * io) {
    FuzzyFunction function;

    ui->cb_currentFuzzyFunction->clear();
    for(int i=0; i<io->fuzzyFunctions.size(); i++) {
        function = io->fuzzyFunctions.at(i);
        qDebug() << function.name;
        ui->cb_currentFuzzyFunction->addItem(function.name, QVariant(i));
    }

}

