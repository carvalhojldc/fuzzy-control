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

    myFuzzy.statusInputD = true;

    ui_rw = new RuleWindow(myFuzzy);
    ui_fw = new FunctionWindow(myFuzzy);

    ui->setupUi(this);

    // threads
    timerFuzzyControl = new QTimer(0);
    timerGraph        = new QTimer(0);

    threadFuzzyControl = new QThread(this);
    threadGraph        = new QThread(this);

    timerFuzzyControl->start(100);
    timerGraph->start(100);

    timerFuzzyControl->moveToThread(threadFuzzyControl);
    connect(timerFuzzyControl, SIGNAL(timeout()), this, SLOT(myFuzzyControl()));

    timerGraph->moveToThread(threadFuzzyControl);
    connect(timerGraph, SIGNAL(timeout()), this, SLOT(myGraph()));
    // end threads

    // Enable_graphs
    connect(ui->cb_channelRead0, SIGNAL(toggled(bool)), ui->cb_showChannel0, SLOT(setEnabled(bool)));
    connect(ui->cb_channelRead1, SIGNAL(toggled(bool)), ui->cb_showChannel1, SLOT(setEnabled(bool)));

    connect(ui->cb_showChannel0,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showChannel1,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showsignalCalc, SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showsignalSend, SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showError,      SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));
    connect(ui->cb_showSetPoint,   SIGNAL(toggled(bool)), this, SLOT(UI_DisplayGraph()));

    // end Enable_graphs

    // config

    for(int i=0; i<typesSigns.size(); i++)
        ui->cb_typesSigns->addItem(typesSigns.at(i), QVariant(i));

    for(int i=0; i<4; i++)
        ui->cb_WriteChannel->addItem("Canal " + QString::number(i), QVariant(i));

    // end config

    connect(ui->pb_configFuzzyFunction, SIGNAL(clicked(bool)), this, SLOT(UI_functionWindow()));
    connect(ui->pb_configFuzzyRules, SIGNAL(clicked(bool)), this, SLOT(UI_ruleWindow()));

    connect(ui->cb_controlFuzzy, SIGNAL(currentIndexChanged(int)), this, SLOT(controlInput(int)));

    for(int i=0; i<myFuzzy.listControl.size(); i++)
        ui->cb_controlFuzzy->addItem(myFuzzy.listControl.at(i), QVariant(i));

    ui->dSpinOffSet->setEnabled(false);
}

MainWindow::~MainWindow()
{
    threadFuzzyControl->quit();
    threadFuzzyControl->wait();

    threadGraph->quit();
    threadGraph->wait();

    delete connection;
    delete ui_rw;
    delete ui_fw;
    delete ui;
}

void MainWindow::connectServer()
{
    //fuzzyControl = new FuzzyControl();

    if(connection->getSatus())
    {
        this->show();
        QString mensagem = "Conectado em " + connection->getIpAdress() + ":" + QString::number(connection->getPort());
        ui->labelStatus->setText(mensagem);
        ui->labelStatus->setStyleSheet("QLabel { color : green; }");

        threadFuzzyControl->start();
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

void MainWindow::controlInput(int id)
{
    if(id == 0) { // fuzzy p
        myFuzzy.statusInputP = true;
        myFuzzy.statusInputI = false;
        myFuzzy.statusInputD = false;
    }
    else if(id == 1) { // fuzzy pi
        myFuzzy.statusInputP = true;
        myFuzzy.statusInputI = true;
        myFuzzy.statusInputD = false;;
    }
    else if(id == 2) { // fuzzy pd
        myFuzzy.statusInputP = true;
        myFuzzy.statusInputI = false;
        myFuzzy.statusInputD = true;
    }
    else if(id == 3) { // fuzzy pid
        myFuzzy.statusInputP = true;
        myFuzzy.statusInputI = true;
        myFuzzy.statusInputD = true;
    }

    qDebug() << myFuzzy.statusInputP << myFuzzy.statusInputI << myFuzzy.statusInputD;
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
    ui->graphRead->yAxis->setRange(0,30);
    ui->graphRead->yAxis->setNumberPrecision(2);
    ui->graphRead->yAxis->setLabel("Nível (cm) ");
    ui->graphRead->xAxis->setSubTickCount(10);

    ui->graphRead->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->graphRead->axisRect(0)->setRangeDrag(Qt::Vertical);
    ui->graphRead->axisRect(0)->setRangeZoom(Qt::Vertical);
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
/*
void MainWindow::receiveData()
{
    if(ui->cb_channelRead0->isChecked());
    if(ui->cb_channelRead1->isChecked());
}

void MainWindow::sendData()
{
    int channel = ui->cb_typesSigns->currentIndex();
    connection->sendSignal(channel, 4);

}
*/
void MainWindow::UI_functionWindow()
{
    if(ui_fw != nullptr) delete ui_fw;

    ui_fw = new FunctionWindow(myFuzzy);

    ui_fw->show();
}

void MainWindow::UI_ruleWindow()
{

}

void MainWindow::myFuzzyControl()
{
    static int i = 0;
    //qDebug() << "fuzzyControl " << i++;
}

void MainWindow::myGraph()
{
    static int i = 0;
    //qDebug() << "graph" << i++;
}
