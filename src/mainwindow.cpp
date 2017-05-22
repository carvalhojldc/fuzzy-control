#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui_rule     = nullptr;
    ui_function = nullptr;

    ui->setupUi(this);

    // Enable_graphs
    {
        connect(ui->cb_channelRead0, SIGNAL(toggled(bool)), ui->cb_showChannel0, SLOT(setEnabled(bool)));
        connect(ui->cb_channelRead1, SIGNAL(toggled(bool)), ui->cb_showChannel1, SLOT(setEnabled(bool)));

        connect(ui->cb_showChannel0,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
        connect(ui->cb_showChannel1,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
        connect(ui->cb_showsignalCalc, SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
        connect(ui->cb_showsignalSend, SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
        connect(ui->cb_showError,      SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
        connect(ui->cb_showSetPoint,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    }
    // END Enable_graphs
    // --------------

    connect(ui->cb_typesSigns, SIGNAL(currentIndexChanged(int)), this, SLOT(UI_configSignal(int)));

    connect(ui->dSpinAmp,       SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));
    connect(ui->dSpinPeriodo,   SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));
    connect(ui->dSpinOffSet,    SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));
    connect(ui->dSpinAux,       SIGNAL(valueChanged(double)), this, SLOT(UI_limitRandInput()));

    connect(ui->rb_mandani, SIGNAL(clicked(bool)), this, SLOT(MandSugStatus()));
    connect(ui->rb_sugeno,  SIGNAL(clicked(bool)), this, SLOT(MandSugStatus()));

    connect(ui->cb_controlFuzzy, SIGNAL(currentIndexChanged(int)), this, SLOT(controlInput(int)));

    connect(ui->pb_configFuzzyFunction, SIGNAL(clicked(bool)), this, SLOT(UI_functionWindow()));
    connect(ui->pb_configFuzzyRules, SIGNAL(clicked(bool)), this, SLOT(UI_ruleWindow()));

    connect(ui->buttonAtualizar, SIGNAL(clicked(bool)), this, SLOT(updateData()));

    // --------------

    // config_ui
    {
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

        controlInput(0);
        MandSugStatus();

        UI_configGraphs();
    }
    // END config_ui


    // UI_connection
    {
        connection = new Connection();
        connection->show();

        connect(connection, SIGNAL(accepted()), this, SLOT(connectServer()));
    }
    // end UI_connection
    // --------------
}

MainWindow::~MainWindow()
{
    delete threadControl;

    if(connection != nullptr)
        delete connection;

    if(ui_rule != nullptr)
        delete ui_rule;

    if(ui_function != nullptr)
        delete ui_function;

    if(ui != nullptr)
        delete ui;

}

void MainWindow::connectServer()
{
    if(connection->getSatus())
    {
        this->show();
        QString mensagem = "Conectado em " + connection->getIpAdress() + ":" + QString::number(connection->getPort());
        ui->labelStatus->setText(mensagem);
        ui->labelStatus->setStyleSheet("QLabel { color : green; }");

        QTimer *timerGraphUpdate = new QTimer(this);
        connect(timerGraphUpdate, SIGNAL(timeout()), this, SLOT(myGraph()));
        timerGraphUpdate->start(timeWindow);

        threadControl = new std::thread(&MainWindow::myFuzzyControl, this);
    }
    else
    {
        QMessageBox::critical(this,tr("Control Quanser - Conexão Falhou!"),
                              tr("Verifique o IP e/ou porta do servidor!"));
        connection->show();
    }
}

void MainWindow::UI_configGraphs()
{
    // write
    ui->graphWrite->legend->setVisible(true);
    ui->graphWrite->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    for(int i=0; i<graphWrite.size(); i++)
    {
         ui->graphWrite->addGraph();
         ui->graphWrite->graph(i)->setAntialiasedFill(false);
         ui->graphWrite->graph(i)->setName(graphWrite.at(i));
         //ui->graphWrite->graph(i)->setPen(QPen(graphWriteColor.at((i))));

         if(i!=0)
             ui->graphWrite->graph(i)->setPen(QPen(graphWriteColor.at(i)));
         else
         {
             QPen pen = QPen(graphWriteColor.at(i));
             pen.setStyle(Qt::DotLine);
             pen.setWidthF(2);
             ui->graphWrite->graph(i)->setPen(pen);
         }

         ui->graphWrite->graph(i)->setVisible(false);
         ui->graphWrite->graph(i)->removeFromLegend();
    }

    ui->graphWrite->xAxis->setLabel("Tempo (s)");
    ui->graphWrite->yAxis->setRange(-5,5);
    ui->graphWrite->yAxis->setNumberPrecision(2);
    ui->graphWrite->yAxis->setLabel("Tensão (V) ");
    ui->graphWrite->xAxis->setSubTickCount(5);

    ui->graphWrite->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->graphWrite->axisRect(0)->setRangeDrag(Qt::Vertical);
    ui->graphWrite->axisRect(0)->setRangeZoom(Qt::Vertical);

    ui->graphWrite->replot();

    // read
    ui->graphRead->legend->setVisible(true);
    ui->graphRead->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    for(int i=0; i<graphRead.size(); i++)
    {
        ui->graphRead->addGraph();
        ui->graphRead->graph(i)->setAntialiasedFill(false);
        ui->graphRead->graph(i)->setName(graphRead.at(i));
        if(i!=1)
            ui->graphRead->graph(i)->setPen(QPen(graphReadColor.at(i)));
        else
        {
            QPen pen = QPen(graphReadColor.at(i));
            pen.setStyle(Qt::DotLine);
            pen.setWidthF(2);
            ui->graphRead->graph(i)->setPen(pen);
        }
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
    if(ui_function != nullptr) {
        delete ui_function;
        ui_function = nullptr;
    }

    ui_function = new FunctionWindow(&myFuzzy);

    ui_function->show();
}

void MainWindow::UI_ruleWindow()
{
   if(ui_rule != nullptr) {
       delete ui_rule;
       ui_rule = nullptr;
   }

    ui_rule = new RuleWindow(&myFuzzy);

    ui_rule->show();
}

void MainWindow::controlInput(int id)
{
    myFuzzy.statusError = false;
    myFuzzy.statusErrorFiDerivative = false;
    myFuzzy.statusErrorSeDerivative = false;

    myFuzzy.type = id;

    if(id == FUZZY_P) { // fuzzy p
        myFuzzy.statusError = true;
    }
    else if(id == FUZZY_PI) { // fuzzy pi
        myFuzzy.statusError = true;
        myFuzzy.statusErrorFiDerivative = true;
    }
    else if(id == FUZZY_PD) { // fuzzy pd
        myFuzzy.statusError = true;
        myFuzzy.statusErrorFiDerivative = true;
    }
    else if(id == FUZZY_PID) { // fuzzy pid
        myFuzzy.statusError = true;
        myFuzzy.statusErrorFiDerivative = true;
        myFuzzy.statusErrorSeDerivative = true;
    }

    myFuzzy.rules.clear();
    myFuzzy.output.Clear();

    if(ui_rule != nullptr) {
        delete ui_rule;
        ui_rule = nullptr;
    }

    if(ui_function != nullptr) {
        delete ui_function;
        ui_function = nullptr;
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
    double max = 4;
    double min = -4;
    if(calculatedSignal > max)
        calculatedSignal = max;
    else if(calculatedSignal < min)
        calculatedSignal = min;

    if(tankLevel_2<=3 && calculatedSignal<0) calculatedSignal = 0;

    if(tankLevel_2>=28 && calculatedSignal>0) calculatedSignal = 0;

    return calculatedSignal;
}

void MainWindow::myFuzzyControl()
{
    double tank1=0.0, tank2=0.0, error_=0.0, sendSignal_=0.0, calculatedSignal_=0.0, fuzzySignal_=0.0;

    while(1)
    {
        auto start = std::chrono::steady_clock::now();

        // work
        {
            auto channelWrite = this->channelWrite;

            //readLeavel1 == true ? tank1 = connection->getSignal(0) : tank1 = 0;
            //readLeavel2 == true ? tank2 = connection->getSignal(1) : tank2 = 0;
            tank1 = connection->getSignal(0);
            tank2 = connection->getSignal(1);

            if(isWrite)
            {
                fuzzySignal_      = fuzzyControl.getControl(tank2);
                error_            = fuzzyControl.getError();
                calculatedSignal_ = carrierSignal(fuzzySignal_);
                sendSignal_       = travel(calculatedSignal_, tank2);

                connection->sendSignal(channelWrite, sendSignal_);
                qDebug() << "sendSignal_: " << sendSignal_;
            }

            this->tankLevel_1      = tank1;
            this->tankLevel_2      = tank2;
            this->error            = error_;
            this->calculatedSignal = calculatedSignal_;
            this->sendSignal       = sendSignal_;
            this->fuzzySignal      = fuzzySignal_;
        }
        // END work

        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - start;

        auto timeToWait = timeWindow - elapsed;
        if(timeToWait > std::chrono::milliseconds::zero())
            std::this_thread::sleep_for(timeToWait);
    }
}

void MainWindow::myGraph()
{
    auto tankLevel_1 = this->tankLevel_1;
    auto tankLevel_2 = this->tankLevel_2;
    auto sendSignal = this->sendSignal;
    auto calculatedSignal = this->calculatedSignal;
    auto error = this->error;
    auto setPoint = this->setPoint;

    qDebug() << "thread - grafico";
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

    ui->graphRead->graph(0)->removeData(timeWrite-120);
    ui->graphRead->graph(1)->removeData(timeWrite-120);
    ui->graphRead->graph(2)->removeData(timeWrite-120);
    ui->graphRead->graph(3)->removeData(timeWrite-120);
    // ---

    ui->graphWrite->xAxis->setRange(timeWrite, 60, Qt::AlignRight);
    ui->graphRead->xAxis->setRange(timeWrite, 60, Qt::AlignRight);

    ui->graphWrite->replot();
    ui->graphRead->replot();

    timeWrite += 0.1;
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

//    channelWrite = ui->cb_WriteChannel->currentIndex();
//    readLeavel1  = ui->cb_channelRead0->isChecked();
//    readLeavel2  = ui->cb_channelRead1->isChecked();

    fuzzyControl.setFuzzy(myFuzzy, setPoint);

    isWrite = true;
}

void MainWindow::MandSugStatus()
{    
    myFuzzy.mamdaniStatus = ui->rb_mandani->isChecked();
    myFuzzy.sugenoStatus  = ui->rb_sugeno->isChecked();

    myFuzzy.output.Clear();
    myFuzzy.rules.clear();

    if(ui_rule != nullptr) {
        delete ui_rule;
        ui_rule = nullptr;
    }

    if(ui_function != nullptr) {
        delete ui_function;
        ui_function = nullptr;
    }
}
