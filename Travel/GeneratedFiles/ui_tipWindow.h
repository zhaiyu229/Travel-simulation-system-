/********************************************************************************
** Form generated from reading UI file 'tipWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPWINDOW_H
#define UI_TIPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tipWindow
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *tipWindow)
    {
        if (tipWindow->objectName().isEmpty())
            tipWindow->setObjectName(QStringLiteral("tipWindow"));
        tipWindow->resize(365, 75);
        centralWidget = new QWidget(tipWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tipWindow->setCentralWidget(centralWidget);

        retranslateUi(tipWindow);

        QMetaObject::connectSlotsByName(tipWindow);
    } // setupUi

    void retranslateUi(QMainWindow *tipWindow)
    {
        tipWindow->setWindowTitle(QApplication::translate("tipWindow", "tipWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tipWindow: public Ui_tipWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPWINDOW_H
