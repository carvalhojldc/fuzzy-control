/********************************************************************************
** Form generated from reading UI file 'connection.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTION_H
#define UI_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Connection
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineIpAdress;
    QLabel *label_2;
    QSpinBox *spinBoxPort;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QPushButton *buttonCancell;
    QPushButton *buttonConnection;
    QCheckBox *cb_simulation;

    void setupUi(QDialog *Connection)
    {
        if (Connection->objectName().isEmpty())
            Connection->setObjectName(QStringLiteral("Connection"));
        Connection->resize(360, 240);
        Connection->setMinimumSize(QSize(360, 240));
        Connection->setMaximumSize(QSize(360, 240));
        layoutWidget = new QWidget(Connection);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 30, 221, 91));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineIpAdress = new QLineEdit(layoutWidget);
        lineIpAdress->setObjectName(QStringLiteral("lineIpAdress"));
        lineIpAdress->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineIpAdress, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinBoxPort = new QSpinBox(layoutWidget);
        spinBoxPort->setObjectName(QStringLiteral("spinBoxPort"));
        spinBoxPort->setEnabled(true);
        spinBoxPort->setMouseTracking(false);
        spinBoxPort->setAlignment(Qt::AlignCenter);
        spinBoxPort->setKeyboardTracking(true);
        spinBoxPort->setMaximum(65535);
        spinBoxPort->setValue(0);

        gridLayout->addWidget(spinBoxPort, 1, 1, 1, 1);

        layoutWidget1 = new QWidget(Connection);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 160, 261, 51));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonCancell = new QPushButton(layoutWidget1);
        buttonCancell->setObjectName(QStringLiteral("buttonCancell"));

        gridLayout_2->addWidget(buttonCancell, 0, 0, 1, 1);

        buttonConnection = new QPushButton(layoutWidget1);
        buttonConnection->setObjectName(QStringLiteral("buttonConnection"));

        gridLayout_2->addWidget(buttonConnection, 0, 1, 1, 1);

        cb_simulation = new QCheckBox(Connection);
        cb_simulation->setObjectName(QStringLiteral("cb_simulation"));
        cb_simulation->setGeometry(QRect(70, 130, 151, 24));

        retranslateUi(Connection);

        QMetaObject::connectSlotsByName(Connection);
    } // setupUi

    void retranslateUi(QDialog *Connection)
    {
        Connection->setWindowTitle(QApplication::translate("Connection", "Control Quanser - Conectar sistema", Q_NULLPTR));
        label->setText(QApplication::translate("Connection", "IP:", Q_NULLPTR));
        lineIpAdress->setText(QString());
        label_2->setText(QApplication::translate("Connection", "Porta:", Q_NULLPTR));
        buttonCancell->setText(QApplication::translate("Connection", "Cancelar", Q_NULLPTR));
        buttonConnection->setText(QApplication::translate("Connection", "Conectar", Q_NULLPTR));
        cb_simulation->setText(QApplication::translate("Connection", "Modo de Simula\303\247\303\243o", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Connection: public Ui_Connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTION_H
