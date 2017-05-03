#include "functionwindow.h"
#include "ui_functionwindow.h"

FunctionWindow::FunctionWindow(Fuzzy &fuzzy, QWidget *parent) :
    QDialog(parent),
    myFuzzy(fuzzy),
    ui(new Ui::FunctionWindow)
{
    ui->setupUi(this);

    connect(ui->rb_inputP, SIGNAL(clicked(bool)), this, SLOT(currentInput()));
    connect(ui->rb_inputI, SIGNAL(clicked(bool)), this, SLOT(currentInput()));
    connect(ui->rb_inputD, SIGNAL(clicked(bool)), this, SLOT(currentInput()));
    connect(ui->rb_output, SIGNAL(clicked(bool)), this, SLOT(currentInput()));

    connect(ui->pb_fuzzyIO,        SIGNAL(clicked(bool)), this, SLOT(insertIORange())  );
    connect(ui->pb_insertFunction, SIGNAL(clicked(bool)), this, SLOT(insertFunction()) );
    connect(ui->pb_editFunction,   SIGNAL(clicked(bool)), this, SLOT(editFunction())   );
    connect(ui->pb_deleteFunction, SIGNAL(clicked(bool)), this, SLOT(deleteFunction()) );

    connect(ui->funcionPlot, SIGNAL(legendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
        this, SLOT(plotterLegendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)));


    for(int i=0; i<myFuzzy.listFuzzyFunctions.size(); i++)
        ui->cb_InsertFunctionType->addItem(myFuzzy.listFuzzyFunctions.at(i), QVariant(i));

    // ---------
    // graph
    ui->funcionPlot->xAxis->setLabel("x");
    ui->funcionPlot->yAxis->setLabel("y");

    ui->funcionPlot->legend->setVisible(true);

    ui->funcionPlot->yAxis->grid()->setSubGridVisible(true);
    ui->funcionPlot->xAxis->grid()->setSubGridVisible(true);

    ui->funcionPlot->xAxis->setRange(-30,30);
    ui->funcionPlot->yAxis->setRange(0,1);

    //Usuário arraste eixo varia com o mouse, zoom com a roda do mouse e selecione gráficos clicando:
    //ui->funcionPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->funcionPlot->setInteractions(QCP::iSelectPlottables );
    //ui->funcionPlot->axisRect(0)->setRangeDrag(Qt::Vertical);
    //ui->funcionPlot->axisRect(0)->setRangeZoom(Qt::Vertical);

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->funcionPlot->plotLayout()->addElement(0, 1, subLayout);
    subLayout->addElement(0, 0, new QCPLayoutElement);
    subLayout->addElement(1, 0, ui->funcionPlot->legend);
    subLayout->addElement(2, 0, new QCPLayoutElement);
    ui->funcionPlot->plotLayout()->setColumnStretchFactor(1, 0.001);

    ui->funcionPlot->replot();
    // end graph

    ui->rb_inputP->setVisible(myFuzzy.statusInputP);
    ui->rb_inputI->setVisible(myFuzzy.statusInputI);
    ui->rb_inputD->setVisible(myFuzzy.statusInputD);
}

FunctionWindow::~FunctionWindow()
{
    delete ui;
}
/*
void FunctionWindow::controlInput(int id)
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
*/
void FunctionWindow::currentInput() {
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
    ui->le_fuzzyRange->setText( QString::number(io->range.at(0)) + " " + QString::number(io->range.at(1)) );
}

FuzzyVariable* FunctionWindow::getIO()
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

void FunctionWindow::updateCurrentData(FuzzyVariable * io) {
    FuzzyFunction function;

    ui->cb_currentFuzzyFunction->clear();
    for(int i=0; i<io->fuzzyFunctions.size(); i++) {
        function = io->fuzzyFunctions.at(i);
        ui->cb_currentFuzzyFunction->addItem(function.name, QVariant(i));
    }
}

void FunctionWindow::insertIORange()
{
    FuzzyVariable *io   = getIO();
    QString titleWindow = "Intervalo";
    QString range       = ui->le_fuzzyRange->text();
    QStringList numberPoints;

    if(io == nullptr) {
        QMessageBox::critical(0, titleWindow,
                "Erro ao buscar Entrada/Saída do sistema!");
        return;
    }

    numberPoints = range.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if( numberPoints.size() != 2 ) { // start and end
        QString message = "Intervalo inválido, insira 2 pontos \
                (separados por espaço) para representar o exito x!";
        QMessageBox::critical(0, titleWindow, message);
        return;
    }

    io->range[0] = numberPoints.at(0).toFloat();
    io->range[1] = numberPoints.at(1).toFloat();

    ui->funcionPlot->xAxis->setRange(io->range[0], io->range[1]);

    for(int i=io->fuzzyFunctions.size()-1; i>=0; i--)
        ui->funcionPlot->removeGraph(i);

    io->fuzzyFunctions.clear();
    updateCurrentData(io);

    ui->funcionPlot->replot();
}

void FunctionWindow::insertFunction()
{
    QString titleWindow = "Inserir função";

    if(ui->le_InsertFunctionName->text().isEmpty())
        QMessageBox::critical(0, titleWindow, "Nome inválido!");
    else if(ui->le_InsertRangeFunction->text().isEmpty())
        QMessageBox::critical(0, titleWindow, "Intervalo inválido!");
    else {

        FuzzyVariable *io = getIO();
        FuzzyFunction newFunction;
        QStringList points;

        // before adding new function
        int graphId = io->fuzzyFunctions.size();

        if(io == nullptr) {
            QMessageBox::critical(0, titleWindow,
                "Erro ao buscar Entrada/Saída do sistema!");
            return;
        }

        newFunction.name  = ui->le_InsertFunctionName->text();

        // validate name
        {
            for(int i=0; i<io->fuzzyFunctions.size(); i++)
                if( newFunction.name  == io->fuzzyFunctions.at(i).name ) {
                    QMessageBox::critical(0, titleWindow,
                        "Nome já utilizado, tente outro!");
                    return;
                }
        }

        newFunction.type = ui->cb_InsertFunctionType->currentIndex();
        points = ( ui->le_InsertRangeFunction->text() ).split(QRegExp("\\s+"), \
                                                            QString::SkipEmptyParts);

        newFunction.range.clear();
        for(int i=0; i<points.size(); i++)
            newFunction.range.push_back( points.at(i).toFloat() );

        // validade range (number of points)
        {
            QString message = "Intervalo inválido, insira " + \
                QString::number(newFunction.getNumberPoints()) + \
                " pontos do eixo x [" + QString::number(io->range[0]) +\
                ", " + QString::number(io->range[1]) + "]!";

            // validate interval
            if( points.size() != newFunction.getNumberPoints() ||
                newFunction.range.at(0) < io->range[0] ||
                newFunction.range.at(newFunction.range.size()-1) > io->range[1] )
            {
                QMessageBox::critical(0, titleWindow, message);
                return;
            }

            // validate order
            for(int i=1; i<newFunction.range.size(); i++)
                if( newFunction.range.at(i-1) > newFunction.range.at(i) )
                {
                    QMessageBox::critical(0, titleWindow, "Ondem do intervalo é inválida!");
                    return;
                }
        }


        /*
            TODO

            verificar se eh mad ou sugeno
        */

        // end of all validation
        // ----------------

        newFunction.generateGraph( (*io).range );

        // config graph
        ui->funcionPlot->addGraph();
        ui->funcionPlot->graph(graphId)->setAntialiasedFill(false);
        ui->funcionPlot->graph(graphId)->setName(newFunction.name);
        ui->funcionPlot->graph(graphId)->setVisible(true);
        ui->funcionPlot->graph(graphId)->addToLegend();
        //ui->funcionPlot->graph(graphId)->setPen(QPen(Qt::black+50*graphId));
        QColor myColor = QColor(rand()%200+10, rand()%200+10, rand()%200+10, 255);
        ui->funcionPlot->graph(graphId)->setPen( QPen(myColor) );
        //ui->funcionPlot->graph(graphId)->setBrush( QBrush(myColor));

        ui->funcionPlot->graph(graphId)->setData(newFunction.graph[0], \
                                                 newFunction.graph[1]);
        ui->funcionPlot->replot();
        // ---

        ui->le_InsertFunctionName->clear();
        ui->le_InsertRangeFunction->clear();
        ui->cb_InsertFunctionType->setCurrentIndex(0);

        io->fuzzyFunctions.push_back(newFunction);

        updateCurrentData(io);
    }
}

void FunctionWindow::deleteFunction(void)
{
    FuzzyVariable *io = getIO();

    int id = ui->cb_currentFuzzyFunction->currentIndex();

    io->fuzzyFunctions.removeAt(id);

    ui->funcionPlot->removeGraph(id);
    ui->funcionPlot->replot();

    updateCurrentData(io);
}

void FunctionWindow::editFunction(void)
{
    FuzzyVariable *io = getIO();

    int id = ui->cb_currentFuzzyFunction->currentIndex();

    FuzzyFunction function = io->fuzzyFunctions.at(id);
    QString funcionName    = function.name;
    QString functionRange  = "";
    int functionType       = function.type;

    for(int i=0; i<function.range.size(); i++)
        functionRange += (QString::number(function.range.at(i)) + " ");

    ui->cb_InsertFunctionType->setCurrentIndex( functionType );
    ui->le_InsertFunctionName->setText( funcionName );
    ui->le_InsertRangeFunction->setText( functionRange );

    deleteFunction();
}

void FunctionWindow::plotterLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me)
{
    Q_UNUSED(me);

    if(l == nullptr || ai == nullptr) return;

    // Check for selection
    if("QCPPlottableLegendItem" == QString(ai->metaObject()->className()))
    {
        for(int i=0; i<l->parentPlot()->graphCount(); i++)
        {
            if( l->parentPlot()->graph(i)->name() == \
                ((QCPPlottableLegendItem*)ai)->plottable()->name() )
            {
                l->parentPlot()->graph(i)->setSelected(!l->parentPlot()->graph(i)->selected());

                ui->cb_currentFuzzyFunction->setCurrentIndex(i);
            }
            else
            {
                l->parentPlot()->graph(i)->setSelected(false);
            }
        }
    }

}
