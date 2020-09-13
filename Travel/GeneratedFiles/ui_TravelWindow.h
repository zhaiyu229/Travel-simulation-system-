/********************************************************************************
** Form generated from reading UI file 'TravelWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAVELWINDOW_H
#define UI_TRAVELWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TravelWindowClass
{
public:
    QWidget *centralWidget;
    QLabel *mapLabel;
    QComboBox *endCity;
    QComboBox *startCity;
    QComboBox *strategy;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *limitEdit;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *selectLabel;
    QDateTimeEdit *startTime;
    QDateTimeEdit *endTime;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *startButton;
    QTextEdit *answerEdit;
    QPushButton *stateButton;
    QTextEdit *stateEdit;
    QLineEdit *sumCost;
    QLineEdit *sumTime;
    QLabel *label;
    QLabel *label_7;

    void setupUi(QMainWindow *TravelWindowClass)
    {
        if (TravelWindowClass->objectName().isEmpty())
            TravelWindowClass->setObjectName(QStringLiteral("TravelWindowClass"));
        TravelWindowClass->resize(1285, 800);
        TravelWindowClass->setMinimumSize(QSize(1285, 800));
        TravelWindowClass->setMaximumSize(QSize(1285, 800));
        centralWidget = new QWidget(TravelWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mapLabel = new QLabel(centralWidget);
        mapLabel->setObjectName(QStringLiteral("mapLabel"));
        mapLabel->setGeometry(QRect(10, 10, 944, 780));
        mapLabel->setFrameShape(QFrame::Box);
        endCity = new QComboBox(centralWidget);
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->addItem(QString());
        endCity->setObjectName(QStringLiteral("endCity"));
        endCity->setGeometry(QRect(1120, 130, 141, 21));
        startCity = new QComboBox(centralWidget);
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->addItem(QString());
        startCity->setObjectName(QStringLiteral("startCity"));
        startCity->setGeometry(QRect(1120, 90, 141, 21));
        strategy = new QComboBox(centralWidget);
        strategy->addItem(QString());
        strategy->addItem(QString());
        strategy->addItem(QString());
        strategy->setObjectName(QStringLiteral("strategy"));
        strategy->setGeometry(QRect(1120, 10, 141, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(970, 10, 91, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(970, 90, 72, 15));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(970, 130, 72, 20));
        limitEdit = new QLineEdit(centralWidget);
        limitEdit->setObjectName(QStringLiteral("limitEdit"));
        limitEdit->setGeometry(QRect(1120, 50, 141, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        limitEdit->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(970, 50, 72, 15));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(970, 170, 101, 16));
        selectLabel = new QLabel(centralWidget);
        selectLabel->setObjectName(QStringLiteral("selectLabel"));
        selectLabel->setGeometry(QRect(970, 190, 301, 131));
        selectLabel->setFrameShape(QFrame::Box);
        startTime = new QDateTimeEdit(centralWidget);
        startTime->setObjectName(QStringLiteral("startTime"));
        startTime->setGeometry(QRect(1070, 330, 201, 21));
        startTime->setReadOnly(true);
        startTime->setCalendarPopup(false);
        startTime->setCurrentSectionIndex(0);
        endTime = new QDateTimeEdit(centralWidget);
        endTime->setObjectName(QStringLiteral("endTime"));
        endTime->setGeometry(QRect(1070, 360, 201, 21));
        endTime->setWrapping(false);
        endTime->setReadOnly(true);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(970, 330, 72, 15));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(970, 360, 72, 15));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(960, 390, 311, 31));
        answerEdit = new QTextEdit(centralWidget);
        answerEdit->setObjectName(QStringLiteral("answerEdit"));
        answerEdit->setGeometry(QRect(960, 430, 311, 235));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        answerEdit->setFont(font1);
        answerEdit->setFrameShape(QFrame::StyledPanel);
        answerEdit->setReadOnly(true);
        stateButton = new QPushButton(centralWidget);
        stateButton->setObjectName(QStringLiteral("stateButton"));
        stateButton->setGeometry(QRect(960, 705, 311, 31));
        stateEdit = new QTextEdit(centralWidget);
        stateEdit->setObjectName(QStringLiteral("stateEdit"));
        stateEdit->setGeometry(QRect(960, 740, 311, 50));
        stateEdit->setFont(font);
        stateEdit->setReadOnly(true);
        sumCost = new QLineEdit(centralWidget);
        sumCost->setObjectName(QStringLiteral("sumCost"));
        sumCost->setGeometry(QRect(1160, 676, 113, 21));
        sumCost->setFont(font);
        sumCost->setReadOnly(true);
        sumTime = new QLineEdit(centralWidget);
        sumTime->setObjectName(QStringLiteral("sumTime"));
        sumTime->setGeometry(QRect(1000, 676, 113, 21));
        sumTime->setFont(font);
        sumTime->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(960, 676, 41, 16));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1120, 676, 41, 16));
        TravelWindowClass->setCentralWidget(centralWidget);

        retranslateUi(TravelWindowClass);

        QMetaObject::connectSlotsByName(TravelWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *TravelWindowClass)
    {
        TravelWindowClass->setWindowTitle(QApplication::translate("TravelWindowClass", "TravelWindow", nullptr));
        mapLabel->setText(QString());
        endCity->setItemText(0, QApplication::translate("TravelWindowClass", "\345\214\227\344\272\254", nullptr));
        endCity->setItemText(1, QApplication::translate("TravelWindowClass", "\344\270\212\346\265\267", nullptr));
        endCity->setItemText(2, QApplication::translate("TravelWindowClass", "\345\223\210\345\260\224\346\273\250", nullptr));
        endCity->setItemText(3, QApplication::translate("TravelWindowClass", "\346\230\206\346\230\216", nullptr));
        endCity->setItemText(4, QApplication::translate("TravelWindowClass", "\346\213\211\350\220\250", nullptr));
        endCity->setItemText(5, QApplication::translate("TravelWindowClass", "\346\265\267\345\217\243", nullptr));
        endCity->setItemText(6, QApplication::translate("TravelWindowClass", "\351\203\221\345\267\236", nullptr));
        endCity->setItemText(7, QApplication::translate("TravelWindowClass", "\345\215\227\344\272\254", nullptr));
        endCity->setItemText(8, QApplication::translate("TravelWindowClass", "\351\225\277\346\262\231", nullptr));
        endCity->setItemText(9, QApplication::translate("TravelWindowClass", "\345\221\274\345\222\214\346\265\251\347\211\271", nullptr));
        endCity->setItemText(10, QApplication::translate("TravelWindowClass", "\346\210\220\351\203\275", nullptr));
        endCity->setItemText(11, QApplication::translate("TravelWindowClass", "\346\255\246\346\261\211", nullptr));

        startCity->setItemText(0, QApplication::translate("TravelWindowClass", "\345\214\227\344\272\254", nullptr));
        startCity->setItemText(1, QApplication::translate("TravelWindowClass", "\344\270\212\346\265\267", nullptr));
        startCity->setItemText(2, QApplication::translate("TravelWindowClass", "\345\223\210\345\260\224\346\273\250", nullptr));
        startCity->setItemText(3, QApplication::translate("TravelWindowClass", "\346\230\206\346\230\216", nullptr));
        startCity->setItemText(4, QApplication::translate("TravelWindowClass", "\346\213\211\350\220\250", nullptr));
        startCity->setItemText(5, QApplication::translate("TravelWindowClass", "\346\265\267\345\217\243", nullptr));
        startCity->setItemText(6, QApplication::translate("TravelWindowClass", "\351\203\221\345\267\236", nullptr));
        startCity->setItemText(7, QApplication::translate("TravelWindowClass", "\345\215\227\344\272\254", nullptr));
        startCity->setItemText(8, QApplication::translate("TravelWindowClass", "\351\225\277\346\262\231", nullptr));
        startCity->setItemText(9, QApplication::translate("TravelWindowClass", "\345\221\274\345\222\214\346\265\251\347\211\271", nullptr));
        startCity->setItemText(10, QApplication::translate("TravelWindowClass", "\346\210\220\351\203\275", nullptr));
        startCity->setItemText(11, QApplication::translate("TravelWindowClass", "\346\255\246\346\261\211", nullptr));

        strategy->setItemText(0, QApplication::translate("TravelWindowClass", "\346\234\200\345\260\221\350\264\271\347\224\250", nullptr));
        strategy->setItemText(1, QApplication::translate("TravelWindowClass", "\346\234\200\345\260\221\346\227\266\351\227\264", nullptr));
        strategy->setItemText(2, QApplication::translate("TravelWindowClass", "\351\231\220\346\227\266\346\234\200\345\260\221\350\264\271\347\224\250", nullptr));

        label_2->setText(QApplication::translate("TravelWindowClass", "\347\255\226\347\225\245\351\200\211\346\213\251:", nullptr));
        label_3->setText(QApplication::translate("TravelWindowClass", "\345\247\213\345\217\221\345\234\260:", nullptr));
        label_4->setText(QApplication::translate("TravelWindowClass", "\347\233\256\347\232\204\345\234\260:", nullptr));
        label_5->setText(QApplication::translate("TravelWindowClass", "\351\231\220\346\227\266\346\227\266\351\227\264:", nullptr));
        label_6->setText(QApplication::translate("TravelWindowClass", "\351\200\211\346\213\251\351\200\224\347\273\217\345\237\216\345\270\202:", nullptr));
        selectLabel->setText(QString());
        startTime->setDisplayFormat(QApplication::translate("TravelWindowClass", "yyyy/MM/dd hh:mm:ss", nullptr));
        endTime->setDisplayFormat(QApplication::translate("TravelWindowClass", "yyyy/MM/dd hh:mm:ss", nullptr));
        label_8->setText(QApplication::translate("TravelWindowClass", "\345\207\272\345\217\221\346\227\266\351\227\264:", nullptr));
        label_9->setText(QApplication::translate("TravelWindowClass", "\345\210\260\350\276\276\346\227\266\351\227\264:", nullptr));
        startButton->setText(QApplication::translate("TravelWindowClass", "\347\224\237\346\210\220\350\267\257\347\272\277", nullptr));
        answerEdit->setHtml(QApplication::translate("TravelWindowClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        stateButton->setText(QApplication::translate("TravelWindowClass", "\346\237\245\350\257\242\345\275\223\345\211\215\347\212\266\346\200\201", nullptr));
        stateEdit->setHtml(QApplication::translate("TravelWindowClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p></body></html>", nullptr));
        label->setText(QApplication::translate("TravelWindowClass", "\350\200\227\346\227\266:", nullptr));
        label_7->setText(QApplication::translate("TravelWindowClass", "\350\264\271\347\224\250:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TravelWindowClass: public Ui_TravelWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAVELWINDOW_H
