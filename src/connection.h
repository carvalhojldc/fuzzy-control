#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDialog>

#include "quanser.h"
#include "tanque.h"

#define PORT_S 20081
#define IP_S "10.13.99.69"

namespace Ui {
class Connection;
}

class Connection : public QDialog
{
    Q_OBJECT

    public:
        explicit Connection(QWidget *parent = 0);
        ~Connection();

        bool getSatus() const;

        QString getIpAdress() const;

        int getPort() const;

        double getSignal(const int channel);

        int sendSignal(const int channel, const double signal);

    private slots:
        void setConnection();

    private:
        Ui::Connection *ui;

        Quanser *quanser;
        QString ipAdress;
        int     port;

        bool simulation;

        Tanque tankSimulation;
};

#endif // CONNECTION_H
