#include "functionwindow.h"
#include "ui_functionwindow.h"

FunctionWindow::FunctionWindow(Fuzzy *fuzzy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionWindow)
{
    myFuzzy = fuzzy;

    ui->setupUi(this);

    io = nullptr;

    ui->rb_error->setEnabled(myFuzzy->statusError);
    ui->rb_errorFD->setEnabled(myFuzzy->statusErrorFiDerivative);
    ui->rb_errorSD->setEnabled(myFuzzy->statusErrorSeDerivative);
    ui->rb_output->setEnabled(true);

    ui->rb_error->setText( myFuzzy->error.name );
    ui->rb_errorFD->setText( myFuzzy->errorFirstDerivative.name );
    ui->rb_errorSD->setText( myFuzzy->errorSecondDerivative.name );
    ui->rb_output->setText( myFuzzy->output.name );

    // ---------------
    // Config graph
    {
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

        // select graph in legend
        connect(ui->funcionPlot, SIGNAL(legendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
            this, SLOT(graphLegendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)));

        connect(ui->funcionPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)),
            this, SLOT(graphClick(QCPAbstractPlottable*, QMouseEvent*)));
    }

    connect(ui->rb_error,   SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));
    connect(ui->rb_errorFD, SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));
    connect(ui->rb_errorSD, SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));
    connect(ui->rb_output,  SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));

    connect(ui->pb_fuzzyIO,        SIGNAL(clicked(bool)), this, SLOT(changeIORange())  );

    connect(ui->pb_insertFunction, SIGNAL(clicked(bool)), this, SLOT(insertFunction())     );
    connect(ui->pb_editFunction,   SIGNAL(clicked(bool)), this, SLOT(editFunction())       );
    connect(ui->pb_deleteFunction, SIGNAL(clicked(bool)), this, SLOT(deleteFunction())     );
    connect(ui->pb_deleteAll,      SIGNAL(clicked(bool)), this, SLOT(deleteAllFunctions()) );

    connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(currentFunctionSugeno()));

    QStringList HorizontalHeaderLabels = {"Nome", "Tipo", "Valores"};
    ui->tableWidget->setColumnCount(HorizontalHeaderLabels.size());
    ui->tableWidget->setHorizontalHeaderLabels(HorizontalHeaderLabels);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHidden(true);

    clearCurrentFunction();

    this->isEdit = false;

    ui->pb_deleteAll->setEnabled(false);
    ui->pb_deleteAll->setStyleSheet("background-color: red");
    ui->pb_deleteFunction->setStyleSheet("background-color: red");
}

FunctionWindow::~FunctionWindow()
{
    delete ui;
}

void FunctionWindow::clearGraph(int & id)
{
    ui->funcionPlot->removeGraph(id);
    ui->funcionPlot->replot();
}

void FunctionWindow::clearAllGraphs(void)
{
    ui->funcionPlot->clearGraphs();
    ui->funcionPlot->replot();
}

void FunctionWindow::clearTable(void)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
}

void FunctionWindow::addGraph(const FuzzyFunction *function, const int & id)
{
    ui->funcionPlot->addGraph();

    ui->funcionPlot->graph( id )->addToLegend();
    ui->funcionPlot->graph( id )->setVisible(true);
    ui->funcionPlot->graph( id )->setAntialiasedFill(false);

    ui->funcionPlot->graph( id )->setName(function->name);

    ui->funcionPlot->graph( id )->setPen( QPen( function->graphColor ) );
    //ui->funcionPlot->graph( id )->setBrush( QBrush( function->graphColor ));

    ui->funcionPlot->graph( id )->setData(function->graph[0], function->graph[1]);

    ui->funcionPlot->replot();
}

void FunctionWindow::addDataTable(const FuzzyFunction *function)
{
    QString currentText = myFuzzy->listSugenoFunctions.at( function->type );
    QString stringPoints = "";
    int i = ui->tableWidget->rowCount();

    for(int i=0; i<function->range.size(); i++)
        stringPoints += ( QString::number( function->range.at(i) ) + " " );

    ui->tableWidget->setRowCount( i + 1 );
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem( function->name ) );
    ui->tableWidget->setItem(i, 1, new QTableWidgetItem( currentText ) );
    ui->tableWidget->setItem(i, 2, new QTableWidgetItem( stringPoints ) );
}

FuzzyVariable * FunctionWindow::getIO(void)
{
    if(      ui->rb_error->isChecked()   ) return &myFuzzy->error;
    else if( ui->rb_errorFD->isChecked() ) return &myFuzzy->errorFirstDerivative;
    else if( ui->rb_errorSD->isChecked() ) return &myFuzzy->errorSecondDerivative;
    else if( ui->rb_output->isChecked()  ) return &myFuzzy->output;
    else return nullptr;
}

bool FunctionWindow::errorIO(void)
{
    if(io == nullptr) {
        QMessageBox::critical(0, "Configuração",
                "Erro ao buscar Entrada/Saída do sistema!");
        return true;
    }
    return false;
}

void FunctionWindow::setCurrentFunction(const int id)
{
    QString range = "";
    for(int i=0; i<io->fuzzyFunctions.at(id).range.size(); i++)
        range += (QString::number(io->fuzzyFunctions.at(id).range[i]) + " ");

    this->currentFunction = id;
    ui->label_currentFunction->setText( "Nome: " + io->fuzzyFunctions.at(id).name);

    if(sugenoAndOut())
        ui->label_currentRange->setText("Valores: " + range);
    else
        ui->label_currentRange->setText("Pontos: " + range);

    ui->label_currentRange->setHidden(false);

    ui->pb_deleteFunction->setEnabled(true);
    ui->pb_editFunction->setEnabled(true);
}

void FunctionWindow::clearCurrentFunction(void)
{
    this->currentFunction = -1;
    ui->label_currentFunction->setText( "Nenhuma função selecionada!");
    ui->label_currentRange->clear();
    ui->label_currentRange->setHidden(true);

    ui->pb_deleteFunction->setEnabled(false);
    ui->pb_editFunction->setEnabled(false);

    if(io != nullptr)
    {
        if(io->fuzzyFunctions.size()!=0)
            ui->pb_deleteAll->setEnabled(true);
        else
            ui->pb_deleteAll->setEnabled(false);
    }
}

bool FunctionWindow::sugenoAndOut()
{
    return ( myFuzzy->sugenoStatus && ui->rb_output->isChecked() );
}

// -------------------
// slots

void FunctionWindow::graphLegendClick(QCPLegend *l, QCPAbstractLegendItem *ai, QMouseEvent *me)
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
                //l->parentPlot()->graph(i)->setSelected(!l->parentPlot()->graph(i)->selected());
                l->parentPlot()->graph(i)->setSelected(true);

                setCurrentFunction(i);
            }
            else
            {
                l->parentPlot()->graph(i)->setSelected(false);
            }
        }
    }

    l->parentPlot()->replot();
}

void FunctionWindow::graphClick(QCPAbstractPlottable *plottable, QMouseEvent* me)
{
    Q_UNUSED(me);

    QString functionName = plottable->name();

    for(int i=0; i<io->fuzzyFunctions.size(); i++)
        if(functionName == io->fuzzyFunctions.at(i).name)
        {
            setCurrentFunction(i);
            break;
        }
}

void FunctionWindow::changeCurrentIO(void)
{
    clearAllGraphs();
    clearTable();
    clearCurrentFunction();

    io = getIO();

    if(errorIO()) return;

    if( sugenoAndOut() ) // variable is Output AND is Sugeno
    {
        ui->funcionPlot->setHidden(true);
        ui->tableWidget->setHidden(false);

        ui->frame->setDisabled(true);

        ui->le_fuzzyRange->clear();

        ui->cb_InsertFunctionType->clear();
        for(int i=0; i<myFuzzy->sugenoMode.size(); i++)
            ui->cb_InsertFunctionType->addItem(myFuzzy->sugenoMode.at(i), QVariant(i));

        ui->lb_x->setText("Valor(es) Sugeno:");
    }
    else // variable is Input/Output AND is Sugeno/Mandani
    {
        ui->funcionPlot->setHidden(false);
        ui->tableWidget->setHidden(true);

        ui->frame->setDisabled(false);

        ui->funcionPlot->xAxis->setRange(io->range.at(0),io->range.at(1));

        ui->le_fuzzyRange->setText( QString::number(io->range.at(0)) + " " + \
                                    QString::number(io->range.at(1)) );

        ui->cb_InsertFunctionType->clear();
        for(int i=0; i<myFuzzy->listFuzzyFunctions.size(); i++)
            ui->cb_InsertFunctionType->addItem(myFuzzy->listFuzzyFunctions.at(i), QVariant(i));

        ui->lb_x->setText("Pontos no exino X");
    }

    // load functions
    FuzzyFunction function;
    for(int i=0; i<io->fuzzyFunctions.size(); i++) {
        function = io->fuzzyFunctions.at(i);

        if( sugenoAndOut() )
            addDataTable(&function);
        else
            addGraph(&function, i);
    }

    if(io->fuzzyFunctions.size()!=0)
        ui->pb_deleteAll->setEnabled(true);
    else
        ui->pb_deleteAll->setEnabled(false);
}

void FunctionWindow::changeIORange(void)
{
    if(errorIO()) return;

    QString range = ui->le_fuzzyRange->text();
    QStringList numberPoints;
    double newStart, newEnd;

    numberPoints = range.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if( numberPoints.size() != 2 ) { // start and end, Ex: -5 4
        QMessageBox::critical(0,
                              "Intervalo",
                              "Intervalo inválido, insira 2 pontos \
                              (separados por espaço) para representar o exito x!");
        return;
    }

    newStart = numberPoints.at(0).toDouble(); // start range
    newEnd   = numberPoints.at(1).toDouble(); // end range

    if(newStart == io->range[0] && newEnd == io->range[1]) return;

    // clear old data
    {
        clearCurrentFunction();

        io->Clear();

        if(sugenoAndOut())
            ui->tableWidget->clear();
        else
            clearAllGraphs();
    }

    io->range[0] = newStart;
    io->range[1] = newEnd;

    ui->funcionPlot->xAxis->setRange(io->range[0], io->range[1]);
    ui->funcionPlot->replot();
}

void FunctionWindow::insertFunction(void)
{
    if(errorIO()) return;

    QString titleWindow;
    FuzzyFunction newFunction;
    QStringList points;
    QString stringPoints;
    int graphId;
    //int rowTable;

    int currentIndex = ui->cb_InsertFunctionType->currentIndex();
    QString currentText = ui->cb_InsertFunctionType->currentText();

    if(ui->le_InsertFunctionName->text().isEmpty())
        QMessageBox::critical(0, titleWindow, "Nome inválido!");
    else if(ui->le_InsertRangeFunction->text().isEmpty())
        QMessageBox::critical(0, titleWindow, "Intervalo inválido!");
    else
    {
        newFunction.name  = ui->le_InsertFunctionName->text();
        newFunction.type  = currentIndex;
        stringPoints      = ui->le_InsertRangeFunction->text();

        // validate name
        for(int i=0; i<io->fuzzyFunctions.size(); i++)
            if( newFunction.name  == io->fuzzyFunctions.at(i).name ) {
                QMessageBox::critical(0, "Nome inválido",
                    "Nome já utilizado, tente outro!");
                return;
            }

        // split string of range
        points = ( stringPoints ).split(QRegExp("\\s+"), QString::SkipEmptyParts);

        // add new range
        newFunction.range.clear();
        for(int i=0; i<points.size(); i++)
            newFunction.range.push_back( points.at(i).toDouble() );

        if( sugenoAndOut() ) // is Sugeno
        {
            titleWindow = "Valores Sugeno";

            int nMultSugeno = 1;
            if(myFuzzy->statusError) nMultSugeno += 1;
            if(myFuzzy->statusErrorFiDerivative) nMultSugeno += 1;
            if(myFuzzy->statusErrorSeDerivative) nMultSugeno += 1;

            // validation
            {
                if(currentIndex == 0) { // const
                    if(points.size() != 1) {
                        QMessageBox::critical(0, titleWindow,
                            "Isira apenas um valor!");
                        return;
                    }
                } else if(currentIndex == 1) { // linear
                    if(points.size() != nMultSugeno) {
                        QMessageBox::critical(0, titleWindow,
                            "Isira " + QString::number(nMultSugeno) + " valores!");
                        return;
                    }
                }
            }
            // END validation
            // --------------

            addDataTable(&newFunction);
        }
        else
        {
            titleWindow = "Inserir função";

            // before adding new function
            graphId = io->fuzzyFunctions.size();

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

            // END validation
            // --------------

            newFunction.generateGraph( (*io).range );

            addGraph(&newFunction, graphId);
        }

        // clear current data
        ui->le_InsertFunctionName->clear();
        ui->le_InsertRangeFunction->clear();
        ui->cb_InsertFunctionType->setCurrentIndex(0);

        // add new function of validation
        io->fuzzyFunctions.push_back(newFunction);
    }

    if( ! ui->pb_deleteAll->isEnabled() )
        ui->pb_deleteAll->setEnabled(true);
}

void FunctionWindow::deleteFunction(void)
{
    if(errorIO()) return;
    if(currentFunction < 0) return;

    // confirm
    {
        if( this->isEdit == false)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Deletar função", \
                "Realmente deseja deletar a função '" \
                                + io->fuzzyFunctions.at(currentFunction).name + "'?", \
                QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::No) return;
        }
        this->isEdit = false;
    }

    if(sugenoAndOut())
    {
        ui->tableWidget->removeRow(currentFunction);
    }
    else
    {
        ui->funcionPlot->removeGraph(currentFunction);
        ui->funcionPlot->replot();
    }

    io->fuzzyFunctions.removeAt(currentFunction);

    clearCurrentFunction();
}

void FunctionWindow::deleteAllFunctions(void)
{
    if(errorIO()) return;

    // confirm
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Deletar funções", \
                "Realmente deseja deletar todas funções de '" + io->name + "'?", \
                QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) return;
    }

    if( sugenoAndOut() )
        clearTable();
    else
        clearAllGraphs();

    io->Clear();

    clearCurrentFunction();
}

void FunctionWindow::editFunction(void)
{
    if(errorIO())
        return;

    this->isEdit = true;

    if(currentFunction < 0)
        return;

    FuzzyFunction function = io->fuzzyFunctions.at(currentFunction);
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

void FunctionWindow::currentFunctionSugeno()
{
    setCurrentFunction(ui->tableWidget->currentRow());
}

// end slots
// -------------------
