#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // UI_connection
    connection = new Connection();
    connection->show();

    connect(connection, SIGNAL(accepted()), this, SLOT(connectServer()));

    // end UI_connection
    // --------------

    ui_rw = nullptr;
    ui_fw = nullptr;

    ui->setupUi(this);

    // Enable_graphs
    connect(ui->cb_channelRead0, SIGNAL(toggled(bool)), ui->cb_showChannel0, SLOT(setEnabled(bool)));
    connect(ui->cb_channelRead1, SIGNAL(toggled(bool)), ui->cb_showChannel1, SLOT(setEnabled(bool)));

    connect(ui->cb_showChannel0,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showChannel1,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showsignalCalc, SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showsignalSend, SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showError,      SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showSetPoint,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));

    connect(ui->cb_typesSigns, SIGNAL(currentIndexChanged(int)), this, SLOT(UI_configSignal(int)));

    // END Enable_graphs
    // --------------

    connect(ui->dSpinAmp,       SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));
    connect(ui->dSpinPeriodo,   SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));
    connect(ui->dSpinOffSet,    SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));
    connect(ui->dSpinAux,       SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));

    connect(ui->rb_mandani, SIGNAL(clicked(bool)), this, SLOT(MandSugStatus()));
    connect(ui->rb_sugeno,  SIGNAL(clicked(bool)), this, SLOT(MandSugStatus()));

    connect(ui->pb_configFuzzyFunction, SIGNAL(clicked(bool)), this, SLOT(UI_functionWindow()));
    connect(ui->pb_configFuzzyRules, SIGNAL(clicked(bool)), this, SLOT(UI_ruleWindow()));

    connect(ui->cb_controlFuzzy, SIGNAL(currentIndexChanged(int)), this, SLOT(controlInput(int)));

    connect(ui->buttonAtualizar, SIGNAL(clicked(bool)), this, SLOT(updateData()));

    // --------------

    // config_ui

    ui->rb_mandani->setChecked(true);
    ui->rb_sugeno->setChecked(false);

    //myFuzzy.statusInputD = true;

    ui->cb_WriteChannel->setDisabled(true);

    // list of signs of write
    for(int i=0; i<typesSigns.size(); i++)
        ui->cb_typesSigns->addItem(typesSigns.at(i), QVariant(i));

    // list of channels
    for(int i=0; i<4; i++)
        ui->cb_WriteChannel->addItem("Canal " + QString::number(i), QVariant(i));

    // list of control fuzzy
    for(int i=0; i<myFuzzy.listControl.size(); i++)
        ui->cb_controlFuzzy->addItem(myFuzzy.listControl.at(i), QVariant(i));

    ui->dSpinOffSet->setEnabled(false);
    ui->dSpinAux->setVisible(false);
    ui->dSpinAux->setVisible(false);

    ui->buttonAtualizar->setStyleSheet("background-color: green");
    ui->buttonStop->setStyleSheet("background-color: red");

    // END config_ui

    controlInput(0);
    MandSugStatus();

    // threads

    threadFuzzyControl = new QThread(this);
    threadGraph        = new QThread(this);

    QTimer *timerGraph = new QTimer(0);
    timerGraph->start( timerSleep );
    timerGraph->moveToThread( threadGraph );

    QTimer *timerControl = new QTimer(0);
    timerControl->start( timerSleep );
    timerControl->moveToThread( threadFuzzyControl );

    connect(timerControl, SIGNAL(timeout()), this, SLOT(myFuzzyControl()));
    connect(timerGraph, SIGNAL(timeout()), this, SLOT(myGraph()));

    // end threads
    // --------------

}

MainWindow::~MainWindow()
{
    threadFuzzyControl->quit();
    threadFuzzyControl->wait();

    threadGraph->quit();
    threadGraph->wait();

    if(connection != nullptr) delete connection;

    if(ui_rw != nullptr) delete ui_rw;

    if(ui_fw != nullptr) delete ui_fw;

    if(ui != nullptr) delete ui;
}

void MainWindow::connectServer()
{
    if(connection->getSatus())
    {
        this->show();
        QString mensagem = "Conectado em " + connection->getIpAdress() + ":" + QString::number(connection->getPort());
        ui->labelStatus->setText(mensagem);
        ui->labelStatus->setStyleSheet("QLabel { color : green; }");

        threadGraph->start();

        UI_configGraphWrite();
        UI_configGraphRead();
    }
    else
    {
        QMessageBox::critical(this,tr("Control Quanser - Conexão Falhou!"),
                              tr("Verifique o IP e/ou porta do servidor!"));
        connection->show();
    }
}

void MainWindow::UI_configGraphWrite()
{
    ui->graphWrite->legend->setVisible(true);
    ui->graphWrite->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    for(int i=0; i<graphWrite.size(); i++)
    {
         ui->graphWrite->addGraph();
         ui->graphWrite->graph(i)->setAntialiasedFill(false);
         ui->graphWrite->graph(i)->setName(graphWrite.at(i));
         ui->graphWrite->graph(i)->setPen(QPen(graphWriteColor.at((i))));
         ui->graphWrite->graph(i)->setVisible(false);
         ui->graphWrite->graph(i)->removeFromLegend();
    }

    ui->graphWrite->xAxis->setLabel("Tempo (s)");
    ui->graphWrite->yAxis->setRange(-4.5,4.5);
    ui->graphWrite->yAxis->setNumberPrecision(2);
    ui->graphWrite->yAxis->setLabel("Tensão (V) ");
    ui->graphWrite->xAxis->setSubTickCount(10);

    //Usuário arraste eixo varia com o mouse, zoom com a roda do mouse e selecione gráficos clicando:
    ui->graphWrite->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->graphWrite->axisRect(0)->setRangeDrag(Qt::Vertical);
    ui->graphWrite->axisRect(0)->setRangeZoom(Qt::Vertical);

    ui->graphWrite->replot();
}

void MainWindow::UI_configGraphRead()
{
    ui->graphRead->legend->setVisible(true);
    ui->graphRead->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    for(int i=0; i<graphRead.size(); i++)
    {
        ui->graphRead->addGraph(); // red line
        ui->graphRead->graph(i)->setAntialiasedFill(false);
        ui->graphRead->graph(i)->setName(graphRead.at(i));
        ui->graphRead->graph(i)->setPen(QPen(graphReadColor.at(i)));
        ui->graphRead->graph(i)->setVisible(false);
        ui->graphRead->graph(i)->removeFromLegend();
    }

    ui->graphRead->xAxis->setLabel("Tempo (s)");
    ui->graphRead->yAxis->setRange(-1,31);
    ui->graphRead->yAxis->setNumberPrecision(2);
    ui->graphRead->yAxis->setLabel("Nível (cm) ");
    ui->graphRead->xAxis->setSubTickCount(10);

    ui->graphRead->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->graphRead->axisRect(0)->setRangeDrag(Qt::Vertical);
    ui->graphRead->axisRect(0)->setRangeZoom(Qt::Vertical);

    ui->graphRead->replot();
}

void MainWindow::UI_DisplayGraph()
{
    QVector<bool> signalWrite;
    QVector<bool> signalRead;

    signalRead.push_back( ui->cb_showError->isChecked() );
    signalRead.push_back( ui->cb_showSetPoint->isChecked() );
    signalRead.push_back( ui->cb_showChannel0->isChecked() );
    signalRead.push_back( ui->cb_showChannel1->isChecked() );

    for(int i=0; i<signalRead.size(); i++)
    {
        ui->graphRead->graph(i)->setVisible( signalRead.at(i) );

        if( signalRead.at(i) )
            ui->graphRead->graph(i)->addToLegend();
        else
            ui->graphRead->graph(i)->removeFromLegend();
    }

    signalWrite.push_back( ui->cb_showsignalSend->isChecked() );
    signalWrite.push_back( ui->cb_showsignalCalc->isChecked() );

    for(int i=0; i<signalWrite.size(); i++)
    {
        ui->graphWrite->graph(i)->setVisible( signalWrite.at(i) );

        if( signalWrite.at(i) )
            ui->graphWrite->graph(i)->addToLegend();
        else
            ui->graphWrite->graph(i)->removeFromLegend();
    }

}

void MainWindow::UI_functionWindow()
{
    if(ui_fw != nullptr) {
        delete ui_fw;
        ui_fw = nullptr;
    }

    ui_fw = new FunctionWindow(&myFuzzy);

    ui_fw->show();
}

void MainWindow::UI_ruleWindow()
{
   if(ui_rw != nullptr) {
       delete ui_rw;
       ui_rw = nullptr;
   }

    ui_rw = new RuleWindow(&myFuzzy);

    ui_rw->show();
}

void MainWindow::controlInput(int id)
{
    myFuzzy.statusError = false;
    myFuzzy.statusErrorFiDerivative = false;
    myFuzzy.statusErrorSeDerivative = false;

    myFuzzy.type = id;

    if(id == 0) { // fuzzy p
        myFuzzy.statusError = true;
    }
    else if(id == 1) { // fuzzy pi
        myFuzzy.statusError = true;
        myFuzzy.statusErrorFiDerivative = true;
    }
    else if(id == 2) { // fuzzy pd
        myFuzzy.statusError = true;
        myFuzzy.statusErrorFiDerivative = true;
    }
    else if(id == 3) { // fuzzy pid
        myFuzzy.statusError = true;
        myFuzzy.statusErrorFiDerivative = true;
        myFuzzy.statusErrorSeDerivative = true;
    }

    myFuzzy.rules.clear();
    myFuzzy.output.Clear();

    if(ui_rw != nullptr) {
        delete ui_rw;
        ui_rw = nullptr;
    }


    if(ui_fw != nullptr) {
        delete ui_fw;
        ui_fw = nullptr;
    }
}

double MainWindow::carrierSignal(double voltage)
{
    if(timeAux > period) timeAux = 0;

    if(signalID == 0)
        return signal.degrau(voltage, offSet);
    else if(signalID == 1)
        return signal.seno(voltage, timeAux, period, offSet);
    else if(signalID == 2)
        return signal.quadrada(voltage, timeAux, period, offSet);
    else if(signalID == 3)
        return  signal.serra(voltage, timeAux, period, offSet);
    else if(signalID == 4) {
        double ampMax = setPoint;
        double ampMin = offSet;
        double durMax = period;
        double durMin = periodMax;

        if(timeAux==0) {
            period = signal.periodoAleatorio(durMax, durMin);
            return signal.aleatorio(ampMax, ampMin);
        }
    }

    timeAux += 0.1;
}

double MainWindow::travel(double calculatedSignal, double tankLevel_2)
{
    if(calculatedSignal > 4)
        calculatedSignal = 4;
    else if(calculatedSignal < -4)
        calculatedSignal = -4;

    if(tankLevel_2<=3 && calculatedSignal<0) calculatedSignal = 0;

    if(tankLevel_2>=28 && calculatedSignal>0) calculatedSignal = 0;

    return calculatedSignal;
}

void MainWindow::myFuzzyControl()
{
    qDebug() << "Controlador Fuzzy";

    {
        if(readLeavel1)
            tankLevel_1 = connection->getSignal(0);
        else
            tankLevel_1 = 0;

        if(readLeavel2)
            tankLevel_2 = connection->getSignal(1);
        else
            tankLevel_2 = 0;
    }

    fuzzySignal = fuzzyControl.getControl(tankLevel_2);
    error = fuzzyControl.getError();


    calculatedSignal = carrierSignal(fuzzySignal);

    sendSignal = travel(calculatedSignal, tankLevel_2);

    // write signal
    connection->sendSignal(channelWrite, sendSignal);
}

void MainWindow::myGraph()
{
    static double timeWrite = 0;

    // write data
    ui->graphWrite->graph(0)->addData(timeWrite, sendSignal);
    ui->graphWrite->graph(1)->addData(timeWrite, calculatedSignal);
    ui->graphWrite->graph(0)->removeData(timeWrite-120);
    ui->graphWrite->graph(1)->removeData(timeWrite-120);
    // ---

    // read data
    ui->graphRead->graph(0)->addData(timeWrite, error);
    ui->graphRead->graph(1)->addData(timeWrite, setPoint);
    ui->graphRead->graph(2)->addData(timeWrite, tankLevel_1);
    ui->graphRead->graph(3)->addData(timeWrite, tankLevel_2);
    // ---

    ui->graphWrite->xAxis->setRange(timeWrite, 60, Qt::AlignRight);
    ui->graphRead->xAxis->setRange(timeWrite, 60, Qt::AlignRight);

    timeWrite += 0.1;
    ui->graphWrite->replot();
    ui->graphRead->replot();

    ui->pb_tanque1->setValue( tankLevel_1 );
    ui->pb_tanque2->setValue( tankLevel_2 );
}

void MainWindow::UI_limitRandInput()
{
    ui->dSpinOffSet->setMaximum(ui->dSpinAmp->value());
    ui->dSpinAux->setMaximum(ui->dSpinPeriodo->value());
    ui->dSpinAmp->setMinimum(ui->dSpinOffSet->value());
    ui->dSpinPeriodo->setMinimum(ui->dSpinAux->value());
}

void MainWindow::UI_configSignal(int signal)
{
    ui->labelOffSet->setEnabled(true);
    ui->labelPeriodo->setEnabled(true);
    ui->dSpinOffSet->setEnabled(true);
    ui->dSpinPeriodo->setEnabled(true);
    ui->dSpinAux->setVisible(false);
    ui->labelAux->setVisible(false);

    if(signal == 0) // signal deg
    {
        ui->labelOffSet->setEnabled(false);
        ui->labelPeriodo->setEnabled(false);
        ui->dSpinOffSet->setEnabled(false);
        ui->dSpinPeriodo->setEnabled(false);
    }
    else if(signal == 4) // signal rand
    {
        ui->dSpinAux->setVisible(true);
        ui->labelAux->setVisible(true);

        ui->dSpinOffSet->setMaximum(ui->dSpinAmp->value());
        ui->dSpinAux->setMaximum(ui->dSpinPeriodo->value());
    }
}

void MainWindow::updateData()
{
    if( ( myFuzzy.statusError && myFuzzy.error.fuzzyFunctions.size() == 0 ) ||
        ( myFuzzy.statusErrorFiDerivative && myFuzzy.errorFirstDerivative.fuzzyFunctions.size() == 0 ) ||
        ( myFuzzy.statusErrorSeDerivative && myFuzzy.errorSecondDerivative.fuzzyFunctions.size() == 0 ) ||
        ( myFuzzy.output.fuzzyFunctions.size() == 0) )
    {
        QMessageBox::warning(0, "Funções", "Defina as funções de todas as entradas e saídas!");
        return;
    }

    if(myFuzzy.rules.size() == 0)
    {
        QMessageBox::warning(0, "Regras", "Defina regras para o Controlador Fuzzy!");
        return;
    }

    signalID  = ui->cb_typesSigns->currentIndex();
    setPoint  = ui->dSpinAmp->value();
    offSet    = ui->dSpinOffSet->value();
    period    = ui->dSpinPeriodo->value();
    periodMax = ui->dSpinAux->value();

    channelWrite = ui->cb_WriteChannel->currentIndex();
    readLeavel1 = ui->cb_channelRead0->isChecked();
    readLeavel2 = ui->cb_channelRead1->isChecked();

    fuzzyControl.setFuzzy(myFuzzy, setPoint);

    if(!threadFuzzyControl->isRunning())
    {
        threadFuzzyControl->start();
    }
}

void MainWindow::MandSugStatus()
{    
    myFuzzy.mamdaniStatus = ui->rb_mandani->isChecked();
    myFuzzy.sugenoStatus  = ui->rb_sugeno->isChecked();

    myFuzzy.output.Clear();
    myFuzzy.rules.clear();

    if(ui_rw != nullptr) {
        delete ui_rw;
        ui_rw = nullptr;
    }
}
