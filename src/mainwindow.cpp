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

    ui->setupUi(this);

    // threads
    timerRead = new QTimer(0);
    timerWrite = new QTimer(0);

    threadRead = new QThread(this);
    threadWrite = new QThread(this);

    timerRead->start(100);
    timerWrite->start(100);

    timerRead->moveToThread(threadRead);
    connect(timerRead, SIGNAL(timeout()), this, SLOT(receiveData()));

    timerWrite->moveToThread(threadWrite);
    connect(timerWrite, SIGNAL(timeout()), this, SLOT(sendData()));
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

    connect(ui->pb_configFuzzyFunction, SIGNAL(clicked(bool)), this, SLOT(configFuzzyFunction()));
}

MainWindow::~MainWindow()
{
    threadWrite->quit();
    threadWrite->wait();

    threadRead->quit();
    threadRead->wait();

    delete fuzzyControl;
    delete connection;
    delete ui;
}

void MainWindow::connectServer()
{
    fuzzyControl = new FuzzyControl();

    if(connection->getSatus())
    {
        this->show();
        QString mensagem = "Conectado em " + connection->getIpAdress() + ":" + QString::number(connection->getPort());
        ui->labelStatus->setText(mensagem);
        ui->labelStatus->setStyleSheet("QLabel { color : green; }");

        threadWrite->start();
        threadRead->start();

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
    QVector<QString> graphWrite = {"Sinal Enviado", "Sinal Calculado"};
    QVector<QString> graphWriteColor = { "blue" , "red" };

    ui->graphWrite->legend->setVisible(true);
    ui->graphWrite->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    for(int i=0; i<graphWrite.size(); i++)
    {
         ui->graphWrite->addGraph();
         ui->graphWrite->graph(i)->setAntialiasedFill(false);
         ui->graphWrite->graph(i)->setName(graphWrite.at(i));
         ui->graphWrite->graph(i)->setPen(QPen(graphWriteColor.at((i))));
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
    QVector<QString> graphRead = { "Erro", "Set Point", "Tanque 1", "Tanque 2" };
    QVector<QString> graphReadColor = { "red", "black", "blue", "green" };

    ui->graphRead->legend->setVisible(true);
    ui->graphRead->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    for(int i=0; i<graphRead.size(); i++)
    {
        ui->graphRead->addGraph(); // red line
        ui->graphRead->graph(i)->setAntialiasedFill(false);
        ui->graphRead->graph(i)->setName(graphRead.at(i));
        ui->graphRead->graph(i)->setPen(QPen(graphReadColor.at(i)));
        //ui->graphRead->graph(i)->setVisible(false);
        //ui->graphRead->graph(i)->removeFromLegend();
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
    if(ui->cb_showChannel0->isChecked())
    {

    }
    else
    {

    }

    if(ui->cb_showChannel1->isChecked())
    {

    }
    else if(ui->cb_showError->isChecked())
    {

    }
    else if(ui->cb_showSetPoint->isChecked())
    {

    }
    else if(ui->cb_showsignalCalc->isChecked())
    {

    }
    else if(ui->cb_showsignalSend->isChecked())
    {

    }
}

void MainWindow::receiveData()
{

}

void MainWindow::sendData()
{

}

void MainWindow::configFuzzyFunction()
{
    fuzzyConfigUI.show();
}
