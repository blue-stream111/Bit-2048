/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLabel *label_21;
    QLabel *label_01;
    QLabel *label_20;
    QLabel *label_22;
    QLabel *label_30;
    QLabel *label_02;
    QLabel *label_11;
    QLabel *label_00;
    QLabel *label_12;
    QLabel *label_23;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_13;
    QLabel *label_03;
    QLabel *labelPrompt;
    QLabel *labelTimer_;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *rk1;
    QLabel *rk2;
    QLabel *score2;
    QLabel *rk3;
    QLabel *score3;
    QLabel *rk4;
    QLabel *score4;
    QLabel *rk5;
    QLabel *score5;
    QLabel *rk6;
    QLabel *score6;
    QLabel *score1;
    QLabel *labelRank;
    QLabel *labelScore_;
    QPushButton *pushStart;
    QPushButton *pushSuspend;
    QPushButton *pushBack;
    QLabel *labelTimer;
    QLabel *labelScore;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(855, 625);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,\n"
"                                      stop:0 #f0f0f0, \n"
"                                      stop:1 #c0c0c0);"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(30, 120, 401, 391));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        label_10->setFont(font);
        label_10->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        label_21 = new QLabel(gridLayoutWidget);
        label_21->setObjectName("label_21");
        label_21->setFont(font);
        label_21->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_21->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_21, 2, 1, 1, 1);

        label_01 = new QLabel(gridLayoutWidget);
        label_01->setObjectName("label_01");
        label_01->setFont(font);
        label_01->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_01->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_01, 0, 1, 1, 1);

        label_20 = new QLabel(gridLayoutWidget);
        label_20->setObjectName("label_20");
        label_20->setFont(font);
        label_20->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_20->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_20, 2, 0, 1, 1);

        label_22 = new QLabel(gridLayoutWidget);
        label_22->setObjectName("label_22");
        label_22->setFont(font);
        label_22->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_22->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_22, 2, 2, 1, 1);

        label_30 = new QLabel(gridLayoutWidget);
        label_30->setObjectName("label_30");
        label_30->setFont(font);
        label_30->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_30->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_30, 3, 0, 1, 1);

        label_02 = new QLabel(gridLayoutWidget);
        label_02->setObjectName("label_02");
        label_02->setFont(font);
        label_02->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_02->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_02, 0, 2, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName("label_11");
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_11, 1, 1, 1, 1);

        label_00 = new QLabel(gridLayoutWidget);
        label_00->setObjectName("label_00");
        label_00->setFont(font);
        label_00->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_00->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_00, 0, 0, 1, 1);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName("label_12");
        label_12->setFont(font);
        label_12->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_12, 1, 2, 1, 1);

        label_23 = new QLabel(gridLayoutWidget);
        label_23->setObjectName("label_23");
        label_23->setFont(font);
        label_23->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_23->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_23, 2, 3, 1, 1);

        label_31 = new QLabel(gridLayoutWidget);
        label_31->setObjectName("label_31");
        label_31->setFont(font);
        label_31->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_31->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_31, 3, 1, 1, 1);

        label_32 = new QLabel(gridLayoutWidget);
        label_32->setObjectName("label_32");
        label_32->setFont(font);
        label_32->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_32->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_32, 3, 2, 1, 1);

        label_33 = new QLabel(gridLayoutWidget);
        label_33->setObjectName("label_33");
        label_33->setFont(font);
        label_33->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_33->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_33, 3, 3, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName("label_13");
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_13->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_13, 1, 3, 1, 1);

        label_03 = new QLabel(gridLayoutWidget);
        label_03->setObjectName("label_03");
        label_03->setFont(font);
        label_03->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 170, 127);\n"
"border:1px solid black\n"
""));
        label_03->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_03, 0, 3, 1, 1);

        labelPrompt = new QLabel(centralwidget);
        labelPrompt->setObjectName("labelPrompt");
        labelPrompt->setGeometry(QRect(30, 40, 371, 41));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        labelPrompt->setFont(font1);
        labelTimer_ = new QLabel(centralwidget);
        labelTimer_->setObjectName("labelTimer_");
        labelTimer_->setGeometry(QRect(460, 160, 101, 41));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        labelTimer_->setFont(font2);
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(680, 117, 171, 271));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        rk1 = new QLabel(formLayoutWidget);
        rk1->setObjectName("rk1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rk1->sizePolicy().hasHeightForWidth());
        rk1->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, rk1);

        rk2 = new QLabel(formLayoutWidget);
        rk2->setObjectName("rk2");
        sizePolicy.setHeightForWidth(rk2->sizePolicy().hasHeightForWidth());
        rk2->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, rk2);

        score2 = new QLabel(formLayoutWidget);
        score2->setObjectName("score2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(score2->sizePolicy().hasHeightForWidth());
        score2->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, score2);

        rk3 = new QLabel(formLayoutWidget);
        rk3->setObjectName("rk3");
        sizePolicy.setHeightForWidth(rk3->sizePolicy().hasHeightForWidth());
        rk3->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, rk3);

        score3 = new QLabel(formLayoutWidget);
        score3->setObjectName("score3");
        sizePolicy.setHeightForWidth(score3->sizePolicy().hasHeightForWidth());
        score3->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, score3);

        rk4 = new QLabel(formLayoutWidget);
        rk4->setObjectName("rk4");
        sizePolicy.setHeightForWidth(rk4->sizePolicy().hasHeightForWidth());
        rk4->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, rk4);

        score4 = new QLabel(formLayoutWidget);
        score4->setObjectName("score4");
        sizePolicy.setHeightForWidth(score4->sizePolicy().hasHeightForWidth());
        score4->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, score4);

        rk5 = new QLabel(formLayoutWidget);
        rk5->setObjectName("rk5");
        sizePolicy.setHeightForWidth(rk5->sizePolicy().hasHeightForWidth());
        rk5->setSizePolicy(sizePolicy);

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, rk5);

        score5 = new QLabel(formLayoutWidget);
        score5->setObjectName("score5");
        sizePolicy.setHeightForWidth(score5->sizePolicy().hasHeightForWidth());
        score5->setSizePolicy(sizePolicy);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, score5);

        rk6 = new QLabel(formLayoutWidget);
        rk6->setObjectName("rk6");
        sizePolicy.setHeightForWidth(rk6->sizePolicy().hasHeightForWidth());
        rk6->setSizePolicy(sizePolicy);

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, rk6);

        score6 = new QLabel(formLayoutWidget);
        score6->setObjectName("score6");
        sizePolicy.setHeightForWidth(score6->sizePolicy().hasHeightForWidth());
        score6->setSizePolicy(sizePolicy);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, score6);

        score1 = new QLabel(formLayoutWidget);
        score1->setObjectName("score1");
        sizePolicy.setHeightForWidth(score1->sizePolicy().hasHeightForWidth());
        score1->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, score1);

        labelRank = new QLabel(centralwidget);
        labelRank->setObjectName("labelRank");
        labelRank->setGeometry(QRect(710, 80, 91, 31));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(false);
        labelRank->setFont(font3);
        labelRank->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelScore_ = new QLabel(centralwidget);
        labelScore_->setObjectName("labelScore_");
        labelScore_->setGeometry(QRect(460, 280, 101, 41));
        labelScore_->setFont(font2);
        pushStart = new QPushButton(centralwidget);
        pushStart->setObjectName("pushStart");
        pushStart->setGeometry(QRect(440, 440, 111, 41));
        pushSuspend = new QPushButton(centralwidget);
        pushSuspend->setObjectName("pushSuspend");
        pushSuspend->setGeometry(QRect(580, 440, 111, 41));
        pushBack = new QPushButton(centralwidget);
        pushBack->setObjectName("pushBack");
        pushBack->setGeometry(QRect(720, 440, 111, 41));
        labelTimer = new QLabel(centralwidget);
        labelTimer->setObjectName("labelTimer");
        labelTimer->setGeometry(QRect(470, 210, 171, 51));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Consolas")});
        font4.setPointSize(28);
        font4.setBold(true);
        labelTimer->setFont(font4);
        labelScore = new QLabel(centralwidget);
        labelScore->setObjectName("labelScore");
        labelScore->setGeometry(QRect(470, 330, 171, 51));
        labelScore->setFont(font4);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 855, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_10->setText(QString());
        label_21->setText(QString());
        label_01->setText(QString());
        label_20->setText(QString());
        label_22->setText(QString());
        label_30->setText(QString());
        label_02->setText(QString());
        label_11->setText(QString());
        label_00->setText(QString());
        label_12->setText(QString());
        label_23->setText(QString());
        label_31->setText(QString());
        label_32->setText(QString());
        label_33->setText(QString());
        label_13->setText(QString());
        label_03->setText(QString());
        labelPrompt->setText(QCoreApplication::translate("MainWindow", "\346\217\220\347\244\272\357\274\232\344\275\277\347\224\250W, S, A, D\346\216\247\345\210\266\344\270\212\343\200\201\344\270\213\343\200\201\345\267\246\343\200\201\345\217\263\347\247\273\345\212\250", nullptr));
        labelTimer_->setText(QCoreApplication::translate("MainWindow", "\350\256\241\346\227\266\345\231\250\357\274\232", nullptr));
        rk1->setText(QString());
        rk2->setText(QString());
        score2->setText(QString());
        rk3->setText(QString());
        score3->setText(QString());
        rk4->setText(QString());
        score4->setText(QString());
        rk5->setText(QString());
        score5->setText(QString());
        rk6->setText(QString());
        score6->setText(QString());
        score1->setText(QString());
        labelRank->setText(QCoreApplication::translate("MainWindow", "\346\216\222\350\241\214\346\246\234", nullptr));
        labelScore_->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\345\210\206\346\225\260\357\274\232", nullptr));
        pushStart->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushSuspend->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        pushBack->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\351\246\226\351\241\265", nullptr));
        labelTimer->setText(QString());
        labelScore->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
