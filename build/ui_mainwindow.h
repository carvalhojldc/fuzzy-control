/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCanal;
    QWidget *centralWidget;
    QGridLayout *gridLayout_19;
    QGridLayout *gridLayout_18;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_12;
    QFrame *groupConectar;
    QGridLayout *gridLayout_17;
    QLabel *labelStatus;
    QGroupBox *gb_configDados;
    QTabWidget *tabWidget;
    QWidget *tabFuzzy;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_21;
    QComboBox *cb_controlFuzzy;
    QPushButton *pb_configFuzzyFunction;
    QPushButton *pb_configFuzzyRules;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_23;
    QRadioButton *rb_sugeno;
    QRadioButton *rb_mandani;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *gb_signal;
    QGridLayout *gridLayout_3;
    QFrame *fm_signal;
    QGridLayout *gridLayout_2;
    QLabel *labelTipoSinal;
    QComboBox *cb_typesSigns;
    QFrame *fm_signalConf;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_11;
    QLabel *labelAmp;
    QLabel *labelOffSet;
    QLabel *labelPeriodo;
    QLabel *labelAux;
    QVBoxLayout *verticalLayout_10;
    QDoubleSpinBox *dSpinAmp;
    QDoubleSpinBox *dSpinOffSet;
    QDoubleSpinBox *dSpinPeriodo;
    QDoubleSpinBox *dSpinAux;
    QSpacerItem *verticalSpacer_2;
    QPushButton *buttonStop;
    QPushButton *buttonAtualizar;
    QWidget *tabChannel;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_7;
    QGroupBox *gp_canalLeitura;
    QGridLayout *gridLayout_5;
    QCheckBox *cb_channelRead0;
    QCheckBox *cb_channelRead1;
    QGroupBox *gp_canalEscrita;
    QGridLayout *gridLayout_4;
    QComboBox *cb_WriteChannel;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_16;
    QGroupBox *gp_graf_se;
    QGridLayout *gridLayout;
    QCheckBox *cb_showsignalCalc;
    QCheckBox *cb_showsignalSend;
    QGroupBox *gp_graf_sl;
    QGridLayout *gridLayout_9;
    QCheckBox *cb_showChannel0;
    QCheckBox *cb_showChannel1;
    QWidget *widget;
    QGridLayout *gridLayout_6;
    QCheckBox *cb_showSetPoint;
    QCheckBox *cb_showError;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_14;
    QCustomPlot *graphWrite;
    QCustomPlot *graphRead;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1188, 799);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionCanal = new QAction(MainWindow);
        actionCanal->setObjectName(QStringLiteral("actionCanal"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_19 = new QGridLayout(centralWidget);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(6);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(6);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(6);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        groupConectar = new QFrame(centralWidget);
        groupConectar->setObjectName(QStringLiteral("groupConectar"));
        groupConectar->setMinimumSize(QSize(354, 34));
        groupConectar->setMaximumSize(QSize(354, 34));
        groupConectar->setFrameShape(QFrame::StyledPanel);
        gridLayout_17 = new QGridLayout(groupConectar);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        labelStatus = new QLabel(groupConectar);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        QFont font;
        font.setFamily(QStringLiteral("Droid Sans Japanese"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        labelStatus->setFont(font);
        labelStatus->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(labelStatus, 0, 0, 1, 1);


        gridLayout_12->addWidget(groupConectar, 0, 0, 1, 1);

        gb_configDados = new QGroupBox(centralWidget);
        gb_configDados->setObjectName(QStringLiteral("gb_configDados"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gb_configDados->sizePolicy().hasHeightForWidth());
        gb_configDados->setSizePolicy(sizePolicy1);
        gb_configDados->setMinimumSize(QSize(354, 580));
        gb_configDados->setMaximumSize(QSize(354, 580));
        tabWidget = new QTabWidget(gb_configDados);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(12, 33, 330, 540));
        tabWidget->setMinimumSize(QSize(330, 540));
        tabWidget->setMaximumSize(QSize(340, 540));
        tabFuzzy = new QWidget();
        tabFuzzy->setObjectName(QStringLiteral("tabFuzzy"));
        gridLayout_11 = new QGridLayout(tabFuzzy);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        groupBox_3 = new QGroupBox(tabFuzzy);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_10 = new QGridLayout(groupBox_3);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setLayoutDirection(Qt::RightToLeft);
        gridLayout_21 = new QGridLayout(groupBox_4);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QStringLiteral("gridLayout_21"));
        cb_controlFuzzy = new QComboBox(groupBox_4);
        cb_controlFuzzy->setObjectName(QStringLiteral("cb_controlFuzzy"));
        cb_controlFuzzy->setLayoutDirection(Qt::LeftToRight);

        gridLayout_21->addWidget(cb_controlFuzzy, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_4, 0, 0, 1, 1);

        pb_configFuzzyFunction = new QPushButton(groupBox_3);
        pb_configFuzzyFunction->setObjectName(QStringLiteral("pb_configFuzzyFunction"));
        pb_configFuzzyFunction->setMinimumSize(QSize(0, 30));
        pb_configFuzzyFunction->setMaximumSize(QSize(16777215, 30));

        gridLayout_10->addWidget(pb_configFuzzyFunction, 2, 0, 1, 1);

        pb_configFuzzyRules = new QPushButton(groupBox_3);
        pb_configFuzzyRules->setObjectName(QStringLiteral("pb_configFuzzyRules"));
        pb_configFuzzyRules->setMinimumSize(QSize(0, 30));
        pb_configFuzzyRules->setMaximumSize(QSize(16777215, 30));

        gridLayout_10->addWidget(pb_configFuzzyRules, 2, 1, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setLayoutDirection(Qt::RightToLeft);
        gridLayout_23 = new QGridLayout(groupBox_5);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        rb_sugeno = new QRadioButton(groupBox_5);
        rb_sugeno->setObjectName(QStringLiteral("rb_sugeno"));
        rb_sugeno->setEnabled(false);
        rb_sugeno->setLayoutDirection(Qt::RightToLeft);
        rb_sugeno->setChecked(true);

        gridLayout_23->addWidget(rb_sugeno, 1, 0, 1, 1);

        rb_mandani = new QRadioButton(groupBox_5);
        rb_mandani->setObjectName(QStringLiteral("rb_mandani"));
        rb_mandani->setEnabled(false);
        rb_mandani->setLayoutDirection(Qt::RightToLeft);
        rb_mandani->setChecked(false);

        gridLayout_23->addWidget(rb_mandani, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_5, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_3, 1, 1, 1, 1);


        gridLayout_11->addWidget(groupBox_3, 0, 0, 1, 2);

        gb_signal = new QGroupBox(tabFuzzy);
        gb_signal->setObjectName(QStringLiteral("gb_signal"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gb_signal->sizePolicy().hasHeightForWidth());
        gb_signal->setSizePolicy(sizePolicy2);
        gb_signal->setMaximumSize(QSize(16777215, 230));
        gb_signal->setLayoutDirection(Qt::LeftToRight);
        gridLayout_3 = new QGridLayout(gb_signal);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        fm_signal = new QFrame(gb_signal);
        fm_signal->setObjectName(QStringLiteral("fm_signal"));
        fm_signal->setFrameShape(QFrame::StyledPanel);
        gridLayout_2 = new QGridLayout(fm_signal);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelTipoSinal = new QLabel(fm_signal);
        labelTipoSinal->setObjectName(QStringLiteral("labelTipoSinal"));
        labelTipoSinal->setLayoutDirection(Qt::RightToLeft);
        labelTipoSinal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelTipoSinal, 0, 0, 1, 1);

        cb_typesSigns = new QComboBox(fm_signal);
        cb_typesSigns->setObjectName(QStringLiteral("cb_typesSigns"));
        cb_typesSigns->setMinimumSize(QSize(130, 0));

        gridLayout_2->addWidget(cb_typesSigns, 0, 1, 1, 1);


        gridLayout_3->addWidget(fm_signal, 0, 0, 1, 1);

        fm_signalConf = new QFrame(gb_signal);
        fm_signalConf->setObjectName(QStringLiteral("fm_signalConf"));
        fm_signalConf->setFrameShape(QFrame::StyledPanel);
        horizontalLayout_5 = new QHBoxLayout(fm_signalConf);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        labelAmp = new QLabel(fm_signalConf);
        labelAmp->setObjectName(QStringLiteral("labelAmp"));
        labelAmp->setLayoutDirection(Qt::LeftToRight);
        labelAmp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelAmp);

        labelOffSet = new QLabel(fm_signalConf);
        labelOffSet->setObjectName(QStringLiteral("labelOffSet"));
        labelOffSet->setLayoutDirection(Qt::LeftToRight);
        labelOffSet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelOffSet);

        labelPeriodo = new QLabel(fm_signalConf);
        labelPeriodo->setObjectName(QStringLiteral("labelPeriodo"));
        labelPeriodo->setLayoutDirection(Qt::LeftToRight);
        labelPeriodo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelPeriodo);

        labelAux = new QLabel(fm_signalConf);
        labelAux->setObjectName(QStringLiteral("labelAux"));
        labelAux->setLayoutDirection(Qt::LeftToRight);
        labelAux->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_11->addWidget(labelAux);


        horizontalLayout_5->addLayout(verticalLayout_11);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        dSpinAmp = new QDoubleSpinBox(fm_signalConf);
        dSpinAmp->setObjectName(QStringLiteral("dSpinAmp"));
        dSpinAmp->setLayoutDirection(Qt::LeftToRight);
        dSpinAmp->setMaximum(30);
        dSpinAmp->setSingleStep(0.5);

        verticalLayout_10->addWidget(dSpinAmp);

        dSpinOffSet = new QDoubleSpinBox(fm_signalConf);
        dSpinOffSet->setObjectName(QStringLiteral("dSpinOffSet"));
        dSpinOffSet->setSingleStep(0.5);

        verticalLayout_10->addWidget(dSpinOffSet);

        dSpinPeriodo = new QDoubleSpinBox(fm_signalConf);
        dSpinPeriodo->setObjectName(QStringLiteral("dSpinPeriodo"));
        dSpinPeriodo->setSingleStep(0.5);

        verticalLayout_10->addWidget(dSpinPeriodo);

        dSpinAux = new QDoubleSpinBox(fm_signalConf);
        dSpinAux->setObjectName(QStringLiteral("dSpinAux"));
        dSpinAux->setSingleStep(0.5);

        verticalLayout_10->addWidget(dSpinAux);


        horizontalLayout_5->addLayout(verticalLayout_10);


        gridLayout_3->addWidget(fm_signalConf, 1, 0, 1, 1);


        gridLayout_11->addWidget(gb_signal, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_11->addItem(verticalSpacer_2, 2, 0, 1, 2);

        buttonStop = new QPushButton(tabFuzzy);
        buttonStop->setObjectName(QStringLiteral("buttonStop"));
        buttonStop->setMinimumSize(QSize(140, 35));
        buttonStop->setMaximumSize(QSize(140, 35));

        gridLayout_11->addWidget(buttonStop, 3, 0, 1, 1);

        buttonAtualizar = new QPushButton(tabFuzzy);
        buttonAtualizar->setObjectName(QStringLiteral("buttonAtualizar"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(buttonAtualizar->sizePolicy().hasHeightForWidth());
        buttonAtualizar->setSizePolicy(sizePolicy3);
        buttonAtualizar->setMinimumSize(QSize(140, 35));
        buttonAtualizar->setMaximumSize(QSize(140, 35));

        gridLayout_11->addWidget(buttonAtualizar, 3, 1, 1, 1);

        tabWidget->addTab(tabFuzzy, QString());
        tabChannel = new QWidget();
        tabChannel->setObjectName(QStringLiteral("tabChannel"));
        gridLayout_8 = new QGridLayout(tabChannel);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        groupBox = new QGroupBox(tabChannel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 150));
        gridLayout_7 = new QGridLayout(groupBox);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gp_canalLeitura = new QGroupBox(groupBox);
        gp_canalLeitura->setObjectName(QStringLiteral("gp_canalLeitura"));
        gp_canalLeitura->setMinimumSize(QSize(0, 65));
        gp_canalLeitura->setMaximumSize(QSize(105, 100));
        gp_canalLeitura->setLayoutDirection(Qt::LeftToRight);
        gridLayout_5 = new QGridLayout(gp_canalLeitura);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        cb_channelRead0 = new QCheckBox(gp_canalLeitura);
        cb_channelRead0->setObjectName(QStringLiteral("cb_channelRead0"));
        cb_channelRead0->setEnabled(false);
        cb_channelRead0->setChecked(true);

        gridLayout_5->addWidget(cb_channelRead0, 0, 0, 1, 1);

        cb_channelRead1 = new QCheckBox(gp_canalLeitura);
        cb_channelRead1->setObjectName(QStringLiteral("cb_channelRead1"));
        cb_channelRead1->setEnabled(false);
        cb_channelRead1->setCheckable(true);
        cb_channelRead1->setChecked(true);

        gridLayout_5->addWidget(cb_channelRead1, 1, 0, 1, 1);


        gridLayout_7->addWidget(gp_canalLeitura, 0, 0, 1, 1);

        gp_canalEscrita = new QGroupBox(groupBox);
        gp_canalEscrita->setObjectName(QStringLiteral("gp_canalEscrita"));
        gp_canalEscrita->setMinimumSize(QSize(104, 66));
        gp_canalEscrita->setMaximumSize(QSize(105, 100));
        gridLayout_4 = new QGridLayout(gp_canalEscrita);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        cb_WriteChannel = new QComboBox(gp_canalEscrita);
        cb_WriteChannel->setObjectName(QStringLiteral("cb_WriteChannel"));
        cb_WriteChannel->setMinimumSize(QSize(80, 27));
        cb_WriteChannel->setMaximumSize(QSize(80, 27));
        cb_WriteChannel->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(cb_WriteChannel, 0, 0, 1, 1);


        gridLayout_7->addWidget(gp_canalEscrita, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tabChannel);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_16 = new QGridLayout(groupBox_2);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gp_graf_se = new QGroupBox(groupBox_2);
        gp_graf_se->setObjectName(QStringLiteral("gp_graf_se"));
        gridLayout = new QGridLayout(gp_graf_se);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cb_showsignalCalc = new QCheckBox(gp_graf_se);
        cb_showsignalCalc->setObjectName(QStringLiteral("cb_showsignalCalc"));
        cb_showsignalCalc->setChecked(false);

        gridLayout->addWidget(cb_showsignalCalc, 0, 2, 1, 1);

        cb_showsignalSend = new QCheckBox(gp_graf_se);
        cb_showsignalSend->setObjectName(QStringLiteral("cb_showsignalSend"));
        cb_showsignalSend->setChecked(false);

        gridLayout->addWidget(cb_showsignalSend, 0, 0, 1, 1);


        gridLayout_16->addWidget(gp_graf_se, 0, 0, 1, 1);

        gp_graf_sl = new QGroupBox(groupBox_2);
        gp_graf_sl->setObjectName(QStringLiteral("gp_graf_sl"));
        gridLayout_9 = new QGridLayout(gp_graf_sl);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        cb_showChannel0 = new QCheckBox(gp_graf_sl);
        cb_showChannel0->setObjectName(QStringLiteral("cb_showChannel0"));
        cb_showChannel0->setEnabled(true);
        cb_showChannel0->setChecked(false);

        gridLayout_9->addWidget(cb_showChannel0, 0, 0, 1, 1);

        cb_showChannel1 = new QCheckBox(gp_graf_sl);
        cb_showChannel1->setObjectName(QStringLiteral("cb_showChannel1"));
        cb_showChannel1->setEnabled(true);
        cb_showChannel1->setCheckable(true);
        cb_showChannel1->setChecked(false);

        gridLayout_9->addWidget(cb_showChannel1, 0, 1, 1, 1);


        gridLayout_16->addWidget(gp_graf_sl, 1, 0, 1, 1);

        widget = new QWidget(groupBox_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 50));
        gridLayout_6 = new QGridLayout(widget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        cb_showSetPoint = new QCheckBox(widget);
        cb_showSetPoint->setObjectName(QStringLiteral("cb_showSetPoint"));

        gridLayout_6->addWidget(cb_showSetPoint, 0, 0, 1, 1);

        cb_showError = new QCheckBox(widget);
        cb_showError->setObjectName(QStringLiteral("cb_showError"));

        gridLayout_6->addWidget(cb_showError, 0, 1, 1, 1);


        gridLayout_16->addWidget(widget, 2, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_2, 1, 0, 1, 1);

        tabWidget->addTab(tabChannel, QString());

        gridLayout_12->addWidget(gb_configDados, 1, 0, 1, 1);


        gridLayout_13->addLayout(gridLayout_12, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_13->addItem(verticalSpacer, 1, 0, 1, 1);


        gridLayout_15->addLayout(gridLayout_13, 0, 0, 1, 1);


        gridLayout_18->addLayout(gridLayout_15, 0, 0, 1, 1);

        gridLayout_14 = new QGridLayout();
        gridLayout_14->setSpacing(6);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        graphWrite = new QCustomPlot(centralWidget);
        graphWrite->setObjectName(QStringLiteral("graphWrite"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(graphWrite->sizePolicy().hasHeightForWidth());
        graphWrite->setSizePolicy(sizePolicy4);
        graphWrite->setMinimumSize(QSize(800, 320));
        graphWrite->setMaximumSize(QSize(9999, 99999));

        gridLayout_14->addWidget(graphWrite, 0, 0, 1, 1);

        graphRead = new QCustomPlot(centralWidget);
        graphRead->setObjectName(QStringLiteral("graphRead"));
        sizePolicy4.setHeightForWidth(graphRead->sizePolicy().hasHeightForWidth());
        graphRead->setSizePolicy(sizePolicy4);
        graphRead->setMinimumSize(QSize(800, 320));
        graphRead->setMaximumSize(QSize(99999, 999999));

        gridLayout_14->addWidget(graphRead, 1, 0, 1, 1);


        gridLayout_18->addLayout(gridLayout_14, 0, 1, 1, 1);


        gridLayout_19->addLayout(gridLayout_18, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(buttonStop, buttonAtualizar);
        QWidget::setTabOrder(buttonAtualizar, cb_channelRead0);
        QWidget::setTabOrder(cb_channelRead0, cb_WriteChannel);
        QWidget::setTabOrder(cb_WriteChannel, cb_showsignalCalc);
        QWidget::setTabOrder(cb_showsignalCalc, cb_showChannel1);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Control Quasar", Q_NULLPTR));
        actionCanal->setText(QApplication::translate("MainWindow", "Canal", Q_NULLPTR));
        labelStatus->setText(QApplication::translate("MainWindow", "Desconectado", Q_NULLPTR));
        gb_configDados->setTitle(QApplication::translate("MainWindow", "Configura\303\247\303\243o", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "L\303\263gica Fuzzy", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Controle", Q_NULLPTR));
        pb_configFuzzyFunction->setText(QApplication::translate("MainWindow", "Configurar fun\303\247\303\265es", Q_NULLPTR));
        pb_configFuzzyRules->setText(QApplication::translate("MainWindow", "Configurar regras", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Modo", Q_NULLPTR));
        rb_sugeno->setText(QApplication::translate("MainWindow", "Sugeno", Q_NULLPTR));
        rb_mandani->setText(QApplication::translate("MainWindow", "Mamdani", Q_NULLPTR));
        gb_signal->setTitle(QApplication::translate("MainWindow", "Sinal de Envio", Q_NULLPTR));
        labelTipoSinal->setText(QApplication::translate("MainWindow", "Tipo:", Q_NULLPTR));
        labelAmp->setText(QApplication::translate("MainWindow", "Amplitude", Q_NULLPTR));
        labelOffSet->setText(QApplication::translate("MainWindow", "Off-set", Q_NULLPTR));
        labelPeriodo->setText(QApplication::translate("MainWindow", "Per\303\255odo", Q_NULLPTR));
        labelAux->setText(QApplication::translate("MainWindow", "Per\303\255odo m\303\241ximo", Q_NULLPTR));
        buttonStop->setText(QApplication::translate("MainWindow", "Parar controlador", Q_NULLPTR));
        buttonAtualizar->setText(QApplication::translate("MainWindow", "Atualizar controlador", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabFuzzy), QApplication::translate("MainWindow", "Controlador Fuzzy", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Canais", Q_NULLPTR));
        gp_canalLeitura->setTitle(QApplication::translate("MainWindow", "Canais de Leitura", Q_NULLPTR));
        cb_channelRead0->setText(QApplication::translate("MainWindow", "Tanque 1", Q_NULLPTR));
        cb_channelRead1->setText(QApplication::translate("MainWindow", "Tanque 2", Q_NULLPTR));
        gp_canalEscrita->setTitle(QApplication::translate("MainWindow", "Canal de Escrita", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Gr\303\241ficos", Q_NULLPTR));
        gp_graf_se->setTitle(QApplication::translate("MainWindow", "Sinais de Escrita", Q_NULLPTR));
        cb_showsignalCalc->setText(QApplication::translate("MainWindow", "Sinal Calculado", Q_NULLPTR));
        cb_showsignalSend->setText(QApplication::translate("MainWindow", "Sinal Enviado", Q_NULLPTR));
        gp_graf_sl->setTitle(QApplication::translate("MainWindow", "Sinal de Leitura", Q_NULLPTR));
        cb_showChannel0->setText(QApplication::translate("MainWindow", "Tanque 1", Q_NULLPTR));
        cb_showChannel1->setText(QApplication::translate("MainWindow", "Tanque 2", Q_NULLPTR));
        cb_showSetPoint->setText(QApplication::translate("MainWindow", "Set Point", Q_NULLPTR));
        cb_showError->setText(QApplication::translate("MainWindow", "Erro", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabChannel), QApplication::translate("MainWindow", "Canais e Gr\303\241ficos", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
