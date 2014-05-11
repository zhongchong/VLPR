/********************************************************************************
** Form generated from reading UI file 'vlpr.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VLPR_H
#define UI_VLPR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VLPRClass
{
public:
    QAction *action;
    QWidget *centralWidget;

    void setupUi(QMainWindow *VLPRClass)
    {
        if (VLPRClass->objectName().isEmpty())
            VLPRClass->setObjectName(QString::fromUtf8("VLPRClass"));
        VLPRClass->resize(600, 400);
        action = new QAction(VLPRClass);
        action->setObjectName(QString::fromUtf8("action"));
        centralWidget = new QWidget(VLPRClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        VLPRClass->setCentralWidget(centralWidget);

        retranslateUi(VLPRClass);

        QMetaObject::connectSlotsByName(VLPRClass);
    } // setupUi

    void retranslateUi(QMainWindow *VLPRClass)
    {
        VLPRClass->setWindowTitle(QApplication::translate("VLPRClass", "VLPR", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("VLPRClass", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VLPRClass: public Ui_VLPRClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VLPR_H
