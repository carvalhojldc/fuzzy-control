#include "functionwindow.h"
#include "ui_functionwindow.h"

FunctionWindow::FunctionWindow(Fuzzy *fuzzy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionWindow)
{
    myFuzzy = fuzzy;

    ui->setupUi(this);

    io = nullptr;

    ui->rb_inputP->setVisible(myFuzzy->statusInputP);
    ui->rb_inputI->setVisible(myFuzzy->statusInputI);
    ui->rb_inputD->setVisible(myFuzzy->statusInputD);
    ui->rb_output->setVisible(true);

    ui->rb_inputP->setText( myFuzzy->inputP.name );
    ui->rb_inputI->setText( myFuzzy->inputI.name );
    ui->rb_inputD->setText( myFuzzy->inputD.name );
    ui->rb_output->setText( myFuzzy->output.name );

    // ---------------

    configGraph();

    connect(ui->rb_inputP, SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));
    connect(ui->rb_inputI, SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));
    connect(ui->rb_inputD, SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));
    connect(ui->rb_output, SIGNAL(clicked(bool)), this, SLOT(changeCurrentIO()));

    connect(ui->pb_fuzzyIO,        SIGNAL(clicked(bool)), this, SLOT(changeIORange())  );

    connect(ui->pb_insertFunction, SIGNAL(clicked(bool)), this, SLOT(insertFunction()) );
    connect(ui->pb_editFunction,   SIGNAL(clicked(bool)), this, SLOT(editFunction())   );
    connect(ui->pb_deleteFunction, SIGNAL(clicked(bool)), this, SLOT(deleteFunction()) );

    //for(int i=0; i<myFuzzy->listFuzzyFunctions.size(); i++)
      //  ui->cb_InsertFunctionType->addItem(myFuzzy->listFuzzyFunctions.at(i), QVariant(i));

    QStringList HorizontalHeaderLabels = {"Nome", "Tipo", "Valores"};
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(HorizontalHeaderLabels);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHidden(true);
}

FunctionWindow::~FunctionWindow()
{
    delete ui;
}

void FunctionWindow::configGraph(void)
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
}

void FunctionWindow::clearGraph(int & id)
{
    ui->funcionPlot->removeGraph(id);
    ui->funcionPlot->replot();
}

void FunctionWindow::clearAllGraphs(void)
{
    for(int i=io->fuzzyFunctions.size()-1; i>=0; i--)
        clearGraph(i);
}

void FunctionWindow::addGraph(const FuzzyFunction *function, const int & id)
{
    //QColor myColor = QColor(rand()%200+10, rand()%200+10, rand()%200+10, 255);

    ui->funcionPlot->addGraph();

    ui->funcionPlot->graph( id )->addToLegend();
    ui->funcionPlot->graph( id )->setVisible(true);
    ui->funcionPlot->graph( id )->setAntialiasedFill(false);

    ui->funcionPlot->graph( id )->setName(function->name);

    ui->funcionPlot->graph( id )->setPen( QPen( function->graphColor ) );
    //ui->funcionPlot->graph( id )->setBrush( QBrush(myColor));

    ui->funcionPlot->graph( id )->setData(function->graph[0], function->graph[1]);

    ui->funcionPlot->replot();
}

bool FunctionWindow::ioError(void)
{
    if(io == nullptr) {
        QMessageBox::critical(0, "Configuração",
                "Erro ao buscar Entrada/Saída do sistema!");
        return true;
    }
    return false;
}

FuzzyVariable * FunctionWindow::getIO(void)
{
    if( ui->rb_inputP->isChecked() ) return &myFuzzy->inputP;
    else if( ui->rb_inputI->isChecked() ) return &myFuzzy->inputI;
    else if( ui->rb_inputD->isChecked() ) return &myFuzzy->inputD;
    else if( ui->rb_output->isChecked() ) return &myFuzzy->output;
    else return nullptr;
}

void FunctionWindow::updateCurrentData(void) {
    FuzzyFunction function;

    ui->cb_currentFuzzyFunction->clear();
    for(int i=0; i<io->fuzzyFunctions.size(); i++) {
        function = io->fuzzyFunctions.at(i);
        ui->cb_currentFuzzyFunction->addItem(function.name, QVariant(i));
    }
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

bool FunctionWindow::sugenoOUT()
{
    return ( myFuzzy->sugenoStatus && ui->rb_output->isChecked() );
}

void FunctionWindow::changeCurrentIO(void)
{
    // clear ui
    if(io != nullptr)
    {
        ui->cb_currentFuzzyFunction->clear();
        clearAllGraphs();
    }

    io = getIO();

    if(ioError()) return;

    if( sugenoOUT() ) // variable is Output AND is Sugeno
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
    else // variable is Input AND is Sugeno/Mandani
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

    FuzzyFunction function;
    for(int i=0; i<io->fuzzyFunctions.size(); i++) {
        function = io->fuzzyFunctions.at(i);
        ui->cb_currentFuzzyFunction->addItem(function.name, QVariant(i));

        if(!sugenoOUT()) addGraph(&function, i);
    }
}

void FunctionWindow::changeIORange(void)
{
    QString range = ui->le_fuzzyRange->text();
    QStringList numberPoints;
    double newStart, newEnd;

    if(ioError()) return;

    numberPoints = range.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if( numberPoints.size() != 2 ) { // start and end, Ex: -5 4
        QMessageBox::critical(0,
                              "Intervalo",
                              "Intervalo inválido, insira 2 pontos \
                              (separados por espaço) para representar o exito x!");
        return;
    }

    newStart = numberPoints.at(0).toDouble(); // start range
    newEnd = numberPoints.at(1).toDouble(); // end range

    if(newStart == io->range[0] && newEnd == io->range[1]) return;

    io->range[0] = newStart;
    io->range[1] = newEnd;

    ui->funcionPlot->xAxis->setRange(io->range[0], io->range[1]);
    ui->funcionPlot->replot();

    clearAllGraphs();
    io->fuzzyFunctions.clear();

    updateCurrentData();
}

void FunctionWindow::insertFunction(void)
{
    if(ioError()) return;

    QString titleWindow;
    FuzzyFunction newFunction;
    QStringList points;
    QString stringPoints;
    int graphId;
    int rowTable;

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

        if( sugenoOUT() )
        {
            // is Sugeno
            // ------------------

            titleWindow = "Valores Sugeno";

            int nMultSugeno = 0;
            if(myFuzzy->statusInputP) nMultSugeno += 1;
            if(myFuzzy->statusInputI) nMultSugeno += 1;
            if(myFuzzy->statusInputD) nMultSugeno += 1;

            nMultSugeno += 1;

            // validation
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
            // END validation
            // --------------

            rowTable = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount( rowTable + 1 );
            ui->tableWidget->setItem(rowTable, 0, new QTableWidgetItem( newFunction.name ) );
            ui->tableWidget->setItem(rowTable, 1, new QTableWidgetItem( currentText ) );
            ui->tableWidget->setItem(rowTable, 2, new QTableWidgetItem( stringPoints ) );
        }
        else
        {
            // is Mandani
            // ------------------

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
        //ui->cb_InsertFunctionType->setCurrentIndex(0);

        // add new function of validation
        io->fuzzyFunctions.push_back(newFunction);

        updateCurrentData();
    }
}

void FunctionWindow::deleteFunction(void)
{
    int id = ui->cb_currentFuzzyFunction->currentIndex();

    io->fuzzyFunctions.removeAt(id);

    if(sugenoOUT())
    {
        ui->tableWidget->removeRow(id);
    }
    else
    {
        ui->funcionPlot->removeGraph(id);
        ui->funcionPlot->replot();
    }

    updateCurrentData();
}

void FunctionWindow::editFunction(void)
{
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

// end slots
// -------------------
