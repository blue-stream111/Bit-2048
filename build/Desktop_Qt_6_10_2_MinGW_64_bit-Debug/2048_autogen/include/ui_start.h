/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start
{
public:
    QPushButton *pushStart;
    QPushButton *pushHelp;
    QPushButton *pushLeave;
    QLabel *label;

    void setupUi(QWidget *start)
    {
        if (start->objectName().isEmpty())
            start->setObjectName("start");
        start->resize(748, 532);
        pushStart = new QPushButton(start);
        pushStart->setObjectName("pushStart");
        pushStart->setGeometry(QRect(270, 250, 181, 71));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        pushStart->setFont(font);
        pushHelp = new QPushButton(start);
        pushHelp->setObjectName("pushHelp");
        pushHelp->setGeometry(QRect(270, 340, 181, 71));
        pushHelp->setFont(font);
        pushLeave = new QPushButton(start);
        pushLeave->setObjectName("pushLeave");
        pushLeave->setGeometry(QRect(270, 430, 181, 71));
        pushLeave->setFont(font);
        label = new QLabel(start);
        label->setObjectName("label");
        label->setGeometry(QRect(143, 65, 451, 141));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(72);
        font1.setBold(true);
        font1.setItalic(true);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(start);

        QMetaObject::connectSlotsByName(start);
    } // setupUi

    void retranslateUi(QWidget *start)
    {
        start->setWindowTitle(QCoreApplication::translate("start", "Form", nullptr));
        pushStart->setText(QCoreApplication::translate("start", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushHelp->setText(QCoreApplication::translate("start", "\345\270\256\345\212\251", nullptr));
        pushLeave->setText(QCoreApplication::translate("start", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("start", "Bit2048", nullptr));
    } // retranslateUi

};

namespace Ui {
    class start: public Ui_start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
