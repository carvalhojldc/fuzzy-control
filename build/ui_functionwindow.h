/********************************************************************************
** Form generated from reading UI file 'functionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONWINDOW_H
#define UI_FUNCTIONWINDOW_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_FunctionWindow
{
public:
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QCustomPlot *funcionPlot;
    QGridLayout *gridLayout_6;
    QTableWidget *tableWidget;
    QGroupBox *gb_io;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_9;
    QRadioButton *rb_error;
    QRadioButton *rb_output;
    QRadioButton *rb_errorFD;
    QRadioButton *rb_errorSD;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLineEdit *le_fuzzyRange;
    QPushButton *pb_fuzzyIO;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *lb_InsertFunctionName;
    QLineEdit *le_InsertRangeFunction;
    QPushButton *pb_insertFunction;
    QComboBox *cb_InsertFunctionType;
    QLabel *lb_x;
    QLabel *label_12;
    QLineEdit *le_InsertFunctionName;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_7;
    QFrame *frame_3;
    QGridLayout *gridLayout_8;
    QLabel *label_currentFunction;
    QLabel *label_currentRange;
    QPushButton *pb_editFunction;
    QPushButton *pb_deleteFunction;
    QPushButton *pb_deleteAll;

    void setupUi(QDialog *FunctionWindow)
    {
        if (FunctionWindow->objectName().isEmpty())
            FunctionWindow->setObjectName(QStringLiteral("FunctionWindow"));
        FunctionWindow->resize(780, 525);
        FunctionWindow->setMinimumSize(QSize(780, 525));
        FunctionWindow->setMaximumSize(QSize(780, 525));
        gridLayout = new QGridLayout(FunctionWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame_2 = new QFrame(FunctionWindow);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(760, 300));
        frame_2->setMaximumSize(QSize(760, 300));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        funcionPlot = new QCustomPlot(frame_2);
        funcionPlot->setObjectName(QStringLiteral("funcionPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(funcionPlot->sizePolicy().hasHeightForWidth());
        funcionPlot->setSizePolicy(sizePolicy);
        funcionPlot->setMinimumSize(QSize(200, 200));
        funcionPlot->setMaximumSize(QSize(740, 280));
        gridLayout_6 = new QGridLayout(funcionPlot);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));

        gridLayout_3->addWidget(funcionPlot, 0, 0, 1, 1);

        tableWidget = new QTableWidget(frame_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_3->addWidget(tableWidget, 0, 1, 1, 1);


        gridLayout->addWidget(frame_2, 0, 0, 1, 3);

        gb_io = new QGroupBox(FunctionWindow);
        gb_io->setObjectName(QStringLiteral("gb_io"));
        gb_io->setMinimumSize(QSize(240, 200));
        gb_io->setMaximumSize(QSize(280, 200));
        gridLayout_4 = new QGridLayout(gb_io);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        rb_error = new QRadioButton(gb_io);
        rb_error->setObjectName(QStringLiteral("rb_error"));

        gridLayout_9->addWidget(rb_error, 0, 0, 1, 1);

        rb_output = new QRadioButton(gb_io);
        rb_output->setObjectName(QStringLiteral("rb_output"));

        gridLayout_9->addWidget(rb_output, 0, 1, 1, 1);

        rb_errorFD = new QRadioButton(gb_io);
        rb_errorFD->setObjectName(QStringLiteral("rb_errorFD"));

        gridLayout_9->addWidget(rb_errorFD, 1, 0, 1, 1);

        rb_errorSD = new QRadioButton(gb_io);
        rb_errorSD->setObjectName(QStringLiteral("rb_errorSD"));

        gridLayout_9->addWidget(rb_errorSD, 2, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_9, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 2, 0, 1, 1);

        frame = new QFrame(gb_io);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(0, 75));
        frame->setMaximumSize(QSize(16777215, 75));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setFamily(QStringLiteral("Bitstream Charter"));
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        le_fuzzyRange = new QLineEdit(frame);
        le_fuzzyRange->setObjectName(QStringLiteral("le_fuzzyRange"));

        gridLayout_5->addWidget(le_fuzzyRange, 0, 1, 1, 1);

        pb_fuzzyIO = new QPushButton(frame);
        pb_fuzzyIO->setObjectName(QStringLiteral("pb_fuzzyIO"));

        gridLayout_5->addWidget(pb_fuzzyIO, 1, 0, 1, 2);


        gridLayout_4->addWidget(frame, 4, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout->addWidget(gb_io, 1, 0, 1, 1);

        groupBox = new QGroupBox(FunctionWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(270, 200));
        groupBox->setMaximumSize(QSize(310, 200));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lb_InsertFunctionName = new QLabel(groupBox);
        lb_InsertFunctionName->setObjectName(QStringLiteral("lb_InsertFunctionName"));
        lb_InsertFunctionName->setFont(font);

        gridLayout_2->addWidget(lb_InsertFunctionName, 0, 0, 1, 1);

        le_InsertRangeFunction = new QLineEdit(groupBox);
        le_InsertRangeFunction->setObjectName(QStringLiteral("le_InsertRangeFunction"));
        le_InsertRangeFunction->setMinimumSize(QSize(127, 26));
        le_InsertRangeFunction->setMaximumSize(QSize(999, 26));

        gridLayout_2->addWidget(le_InsertRangeFunction, 2, 1, 1, 1);

        pb_insertFunction = new QPushButton(groupBox);
        pb_insertFunction->setObjectName(QStringLiteral("pb_insertFunction"));
        pb_insertFunction->setMinimumSize(QSize(127, 26));
        pb_insertFunction->setMaximumSize(QSize(999, 26));

        gridLayout_2->addWidget(pb_insertFunction, 3, 1, 1, 1);

        cb_InsertFunctionType = new QComboBox(groupBox);
        cb_InsertFunctionType->setObjectName(QStringLiteral("cb_InsertFunctionType"));
        cb_InsertFunctionType->setMinimumSize(QSize(127, 26));
        cb_InsertFunctionType->setMaximumSize(QSize(999, 26));

        gridLayout_2->addWidget(cb_InsertFunctionType, 1, 1, 1, 1);

        lb_x = new QLabel(groupBox);
        lb_x->setObjectName(QStringLiteral("lb_x"));
        lb_x->setFont(font);

        gridLayout_2->addWidget(lb_x, 2, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);

        gridLayout_2->addWidget(label_12, 1, 0, 1, 1);

        le_InsertFunctionName = new QLineEdit(groupBox);
        le_InsertFunctionName->setObjectName(QStringLiteral("le_InsertFunctionName"));
        le_InsertFunctionName->setMinimumSize(QSize(127, 26));
        le_InsertFunctionName->setMaximumSize(QSize(999, 26));

        gridLayout_2->addWidget(le_InsertFunctionName, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox, 1, 1, 1, 1);

        groupBox_5 = new QGroupBox(FunctionWindow);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(220, 200));
        groupBox_5->setMaximumSize(QSize(230, 200));
        gridLayout_7 = new QGridLayout(groupBox_5);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        frame_3 = new QFrame(groupBox_5);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_3);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_currentFunction = new QLabel(frame_3);
        label_currentFunction->setObjectName(QStringLiteral("label_currentFunction"));
        label_currentFunction->setTextFormat(Qt::RichText);
        label_currentFunction->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_currentFunction->setWordWrap(true);

        gridLayout_8->addWidget(label_currentFunction, 0, 0, 1, 1);

        label_currentRange = new QLabel(frame_3);
        label_currentRange->setObjectName(QStringLiteral("label_currentRange"));

        gridLayout_8->addWidget(label_currentRange, 1, 0, 1, 1);


        gridLayout_7->addWidget(frame_3, 0, 0, 1, 2);

        pb_editFunction = new QPushButton(groupBox_5);
        pb_editFunction->setObjectName(QStringLiteral("pb_editFunction"));

        gridLayout_7->addWidget(pb_editFunction, 1, 0, 1, 1);

        pb_deleteFunction = new QPushButton(groupBox_5);
        pb_deleteFunction->setObjectName(QStringLiteral("pb_deleteFunction"));

        gridLayout_7->addWidget(pb_deleteFunction, 1, 1, 1, 1);

        pb_deleteAll = new QPushButton(groupBox_5);
        pb_deleteAll->setObjectName(QStringLiteral("pb_deleteAll"));

        gridLayout_7->addWidget(pb_deleteAll, 2, 0, 1, 2);


        gridLayout->addWidget(groupBox_5, 1, 2, 1, 1);

        QWidget::setTabOrder(rb_error, rb_errorFD);
        QWidget::setTabOrder(rb_errorFD, rb_errorSD);
        QWidget::setTabOrder(rb_errorSD, rb_output);
        QWidget::setTabOrder(rb_output, le_fuzzyRange);
        QWidget::setTabOrder(le_fuzzyRange, pb_fuzzyIO);
        QWidget::setTabOrder(pb_fuzzyIO, le_InsertFunctionName);
        QWidget::setTabOrder(le_InsertFunctionName, cb_InsertFunctionType);
        QWidget::setTabOrder(cb_InsertFunctionType, le_InsertRangeFunction);
        QWidget::setTabOrder(le_InsertRangeFunction, pb_insertFunction);
        QWidget::setTabOrder(pb_insertFunction, pb_editFunction);
        QWidget::setTabOrder(pb_editFunction, pb_deleteFunction);
        QWidget::setTabOrder(pb_deleteFunction, tableWidget);

        retranslateUi(FunctionWindow);

        QMetaObject::connectSlotsByName(FunctionWindow);
    } // setupUi

    void retranslateUi(QDialog *FunctionWindow)
    {
        FunctionWindow->setWindowTitle(QApplication::translate("FunctionWindow", "Fun\303\247\303\265es de Pertin\303\252ncia do Controlador Fuzzy", Q_NULLPTR));
        gb_io->setTitle(QApplication::translate("FunctionWindow", "Vari\303\241veis", Q_NULLPTR));
        rb_error->setText(QApplication::translate("FunctionWindow", "Entrada 1", Q_NULLPTR));
        rb_output->setText(QApplication::translate("FunctionWindow", "Sa\303\255da", Q_NULLPTR));
        rb_errorFD->setText(QApplication::translate("FunctionWindow", "Entrada 2", Q_NULLPTR));
        rb_errorSD->setText(QApplication::translate("FunctionWindow", "Entrada 3", Q_NULLPTR));
        label_4->setText(QApplication::translate("FunctionWindow", "Intervalo", Q_NULLPTR));
        pb_fuzzyIO->setText(QApplication::translate("FunctionWindow", "Atualizar", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("FunctionWindow", "Configura\303\247\303\243o de fun\303\247\303\265es", Q_NULLPTR));
        lb_InsertFunctionName->setText(QApplication::translate("FunctionWindow", "Nome da fun\303\247\303\243o", Q_NULLPTR));
        pb_insertFunction->setText(QApplication::translate("FunctionWindow", "Inserir", Q_NULLPTR));
        lb_x->setText(QApplication::translate("FunctionWindow", "Pontos no exino X", Q_NULLPTR));
        label_12->setText(QApplication::translate("FunctionWindow", "Tipo", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("FunctionWindow", "Fun\303\247\303\243o corrente", Q_NULLPTR));
        label_currentFunction->setText(QApplication::translate("FunctionWindow", "Nenhuma fun\303\247\303\243o selecionada", Q_NULLPTR));
        label_currentRange->setText(QString());
        pb_editFunction->setText(QApplication::translate("FunctionWindow", "Editar", Q_NULLPTR));
        pb_deleteFunction->setText(QApplication::translate("FunctionWindow", "Apagar", Q_NULLPTR));
        pb_deleteAll->setText(QApplication::translate("FunctionWindow", "Apagar todas", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FunctionWindow: public Ui_FunctionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONWINDOW_H
