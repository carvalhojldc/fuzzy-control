/********************************************************************************
** Form generated from reading UI file 'rulewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULEWINDOW_H
#define UI_RULEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RuleWindow
{
public:
    QGridLayout *gridLayout_14;
    QFrame *frame_2;
    QGridLayout *gridLayout_6;
    QTableWidget *tableWidget;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QWidget *widget_3;
    QGridLayout *gridLayout_11;
    QGridLayout *gl_i3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLabel *label_7;
    QWidget *widget;
    QGridLayout *gridLayout_7;
    QGridLayout *gl_i1;
    QLabel *label_6;
    QGridLayout *gridLayout_4;
    QComboBox *comboBox_1;
    QLabel *label_1;
    QPushButton *insertRule;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_8;
    QGridLayout *gl_i2;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_5;
    QWidget *widget_4;
    QGridLayout *gridLayout_9;
    QGridLayout *gL_o;
    QLabel *label_8;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_12;
    QPushButton *removeRule;
    QLabel *label_currentRule;
    QFrame *frame_3;
    QGridLayout *gridLayout_10;
    QLabel *label_numberRules;
    QLabel *label_nrt;

    void setupUi(QDialog *RuleWindow)
    {
        if (RuleWindow->objectName().isEmpty())
            RuleWindow->setObjectName(QStringLiteral("RuleWindow"));
        RuleWindow->resize(750, 490);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RuleWindow->sizePolicy().hasHeightForWidth());
        RuleWindow->setSizePolicy(sizePolicy);
        RuleWindow->setMinimumSize(QSize(750, 490));
        RuleWindow->setMaximumSize(QSize(750, 490));
        gridLayout_14 = new QGridLayout(RuleWindow);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        frame_2 = new QFrame(RuleWindow);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(732, 270));
        frame_2->setMaximumSize(QSize(732, 270));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        tableWidget = new QTableWidget(frame_2);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(715, 250));
        tableWidget->setMaximumSize(QSize(715, 250));
        tableWidget->setColumnCount(1);
        tableWidget->horizontalHeader()->setVisible(false);

        gridLayout_6->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout_14->addWidget(frame_2, 0, 0, 1, 1);

        frame = new QFrame(RuleWindow);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(732, 90));
        frame->setMaximumSize(QSize(732, 90));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        widget_3 = new QWidget(frame);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_11 = new QGridLayout(widget_3);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gl_i3 = new QGridLayout();
        gl_i3->setObjectName(QStringLiteral("gl_i3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        comboBox_3 = new QComboBox(widget_3);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 1, 0, 1, 1);


        gl_i3->addLayout(gridLayout, 0, 1, 1, 1);

        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gl_i3->addWidget(label_7, 0, 0, 1, 1);


        gridLayout_11->addLayout(gl_i3, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget_3, 0, 2, 1, 1);

        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_7 = new QGridLayout(widget);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gl_i1 = new QGridLayout();
        gl_i1->setObjectName(QStringLiteral("gl_i1"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setLayoutDirection(Qt::RightToLeft);
        label_6->setAlignment(Qt::AlignCenter);

        gl_i1->addWidget(label_6, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        comboBox_1 = new QComboBox(widget);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));

        gridLayout_4->addWidget(comboBox_1, 1, 0, 1, 1);

        label_1 = new QLabel(widget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_1, 0, 0, 1, 1);


        gl_i1->addLayout(gridLayout_4, 0, 1, 1, 1);


        gridLayout_7->addLayout(gl_i1, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget, 0, 0, 1, 1);

        insertRule = new QPushButton(frame);
        insertRule->setObjectName(QStringLiteral("insertRule"));
        insertRule->setMinimumSize(QSize(110, 50));
        insertRule->setMaximumSize(QSize(110, 50));

        gridLayout_5->addWidget(insertRule, 0, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_8 = new QGridLayout(widget_2);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gl_i2 = new QGridLayout();
        gl_i2->setObjectName(QStringLiteral("gl_i2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(widget_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_3->addWidget(comboBox_2, 1, 0, 1, 1);


        gl_i2->addLayout(gridLayout_3, 0, 1, 1, 1);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gl_i2->addWidget(label_5, 0, 0, 1, 1);


        gridLayout_8->addLayout(gl_i2, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget_2, 0, 1, 1, 1);

        widget_4 = new QWidget(frame);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        gridLayout_9 = new QGridLayout(widget_4);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gL_o = new QGridLayout();
        gL_o->setObjectName(QStringLiteral("gL_o"));
        label_8 = new QLabel(widget_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gL_o->addWidget(label_8, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        comboBox_4 = new QComboBox(widget_4);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 1, 0, 1, 1);


        gL_o->addLayout(gridLayout_2, 0, 1, 1, 1);


        gridLayout_9->addLayout(gL_o, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget_4, 0, 3, 1, 1);


        gridLayout_14->addWidget(frame, 1, 0, 1, 1);

        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        groupBox = new QGroupBox(RuleWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_12 = new QGridLayout(groupBox);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        removeRule = new QPushButton(groupBox);
        removeRule->setObjectName(QStringLiteral("removeRule"));
        removeRule->setMinimumSize(QSize(110, 35));
        removeRule->setMaximumSize(QSize(110, 35));

        gridLayout_12->addWidget(removeRule, 0, 1, 1, 1);

        label_currentRule = new QLabel(groupBox);
        label_currentRule->setObjectName(QStringLiteral("label_currentRule"));
        label_currentRule->setMinimumSize(QSize(0, 35));
        label_currentRule->setMaximumSize(QSize(16777215, 35));
        label_currentRule->setTextFormat(Qt::AutoText);
        label_currentRule->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_currentRule->setWordWrap(true);

        gridLayout_12->addWidget(label_currentRule, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBox, 0, 0, 1, 1);

        frame_3 = new QFrame(RuleWindow);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(180, 80));
        frame_3->setMaximumSize(QSize(180, 80));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_10 = new QGridLayout(frame_3);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        label_numberRules = new QLabel(frame_3);
        label_numberRules->setObjectName(QStringLiteral("label_numberRules"));
        label_numberRules->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_numberRules, 0, 1, 1, 1);

        label_nrt = new QLabel(frame_3);
        label_nrt->setObjectName(QStringLiteral("label_nrt"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_nrt->setFont(font);

        gridLayout_10->addWidget(label_nrt, 0, 0, 1, 1);


        gridLayout_13->addWidget(frame_3, 0, 1, 1, 1);


        gridLayout_14->addLayout(gridLayout_13, 2, 0, 1, 1);

        QWidget::setTabOrder(comboBox_1, comboBox_2);
        QWidget::setTabOrder(comboBox_2, comboBox_3);
        QWidget::setTabOrder(comboBox_3, comboBox_4);
        QWidget::setTabOrder(comboBox_4, insertRule);
        QWidget::setTabOrder(insertRule, tableWidget);
        QWidget::setTabOrder(tableWidget, removeRule);

        retranslateUi(RuleWindow);

        QMetaObject::connectSlotsByName(RuleWindow);
    } // setupUi

    void retranslateUi(QDialog *RuleWindow)
    {
        RuleWindow->setWindowTitle(QApplication::translate("RuleWindow", "Regras do Controlador Fuzzy", Q_NULLPTR));
        label_3->setText(QApplication::translate("RuleWindow", "Entrada 3", Q_NULLPTR));
        label_7->setText(QApplication::translate("RuleWindow", "E", Q_NULLPTR));
        label_6->setText(QApplication::translate("RuleWindow", "SE", Q_NULLPTR));
        label_1->setText(QApplication::translate("RuleWindow", "Entrada1", Q_NULLPTR));
        insertRule->setText(QApplication::translate("RuleWindow", "Adicionar regra", Q_NULLPTR));
        label_2->setText(QApplication::translate("RuleWindow", "Entrada2", Q_NULLPTR));
        label_5->setText(QApplication::translate("RuleWindow", "E", Q_NULLPTR));
        label_8->setText(QApplication::translate("RuleWindow", "ENTR\303\203O", Q_NULLPTR));
        label_4->setText(QApplication::translate("RuleWindow", "Sa\303\255da", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("RuleWindow", "Regra selecionada", Q_NULLPTR));
        removeRule->setText(QApplication::translate("RuleWindow", "Deletar regra", Q_NULLPTR));
        label_currentRule->setText(QApplication::translate("RuleWindow", "Nenhuma regra selecionada", Q_NULLPTR));
        label_numberRules->setText(QApplication::translate("RuleWindow", "0", Q_NULLPTR));
        label_nrt->setText(QApplication::translate("RuleWindow", "N\303\272mero de regras: ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RuleWindow: public Ui_RuleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULEWINDOW_H
