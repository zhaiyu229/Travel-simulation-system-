/********************************************************************************
** Form generated from reading UI file 'Tip.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIP_H
#define UI_TIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tip
{
public:
    QLabel *label;

    void setupUi(QWidget *Tip)
    {
        if (Tip->objectName().isEmpty())
            Tip->setObjectName(QStringLiteral("Tip"));
        Tip->resize(400, 115);
        label = new QLabel(Tip);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 20, 72, 15));

        retranslateUi(Tip);

        QMetaObject::connectSlotsByName(Tip);
    } // setupUi

    void retranslateUi(QWidget *Tip)
    {
        Tip->setWindowTitle(QApplication::translate("Tip", "Tip", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tip: public Ui_Tip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIP_H
