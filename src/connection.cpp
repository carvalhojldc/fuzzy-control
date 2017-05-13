#include "connection.h"
#include "ui_connection.h"

Connection::Connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);

    quanser = nullptr;
    simulation = false;

    ui->lineIpAdress->setInputMask(QString("000.000.000.000"));
    ui->lineIpAdress->setValidator(new QRegExpValidator(QRegExp("[0-255].[0-255].[0-255].[0-255]", Qt::CaseInsensitive), this));
    ui->lineIpAdress->setValidator(new QIntValidator(1, 65535, this));

    //connect(ui->spinBoxPort,      SIGNAL(valueChanged(int)),    this, SLOT(setConnection()));
    //connect(ui->lineIpAdress,     SIGNAL(textChanged(QString)), this, SLOT(setConnection()));
    connect(ui->buttonConnection, SIGNAL(clicked(bool)),        this, SLOT(setConnection()));
    connect(ui->buttonCancell,    SIGNAL(clicked(bool)),        this, SLOT(reject()));

    ui->buttonCancell->setStyleSheet("background-color: red");
    ui->buttonConnection->setStyleSheet("background-color: blue");

    ui->spinBoxPort->setValue(PORT_S);
    ui->lineIpAdress->setText(IP_S);

    ipAdress = IP_S;
    port     = PORT_S;
}

Connection::~Connection()
{
    if(quanser != nullptr)
        delete quanser;

    delete ui;
}

void Connection::setConnection()
{
    port     = ui->spinBoxPort->value();
    ipAdress = ui->lineIpAdress->text();

    simulation = ui->cb_simulation->isChecked();

    if(simulation == false)
    {
        quanser = new Quanser(ipAdress.toLatin1().data(), port);

        if(quanser->getStatus() == false)
        {
            delete quanser;
            quanser = nullptr;
        }
    }

    this->hide();
    emit accepted();
}

bool Connection::getSatus() const
{
    if(this->simulation) return this->simulation;

    if(quanser == nullptr)
        return false;

    return quanser->getStatus();
}

int Connection::getPort() const
{ return port; }

QString Connection::getIpAdress() const
{ return ipAdress; }

double Connection::getSignal(const int channel)
{
    if(simulation)
    {
        if(channel == 0) return tankSimulation.getNivelTq1();
        else return tankSimulation.getNivelTq2();
    }
    else
        return quanser->readAD(channel);
}

int Connection::sendSignal(const int channel, const double signal)
{
    if(simulation)
    {
        tankSimulation.acionaBomba(signal);

        tankSimulation.escoaTanque1(tankSimulation.getNivelTq1());
        tankSimulation.escoaTanque2(tankSimulation.getNivelTq2());
    }
    else
        return quanser->writeDA(channel, (float)signal);
}


