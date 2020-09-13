#pragma once

#define MAXPASSCITY 3
#include <QtWidgets/QMainWindow>
#include "ui_TravelWindow.h"
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QPixMap>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QCheckBox>
#include <QString>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QLineEdit>
#include "TimeTable.h"
#include "Solution.h"
#include "TipWindow.h"
using namespace std;
#define PERSECONDHOURS 2 //ÿ���Ӧ��Сʱ��

class TravelWindow : public QMainWindow
{
	Q_OBJECT

public:
	TravelWindow(QWidget *parent = Q_NULLPTR);
	void setCityNames();//Ϊѡ��;�����и�����ť�����ϳ��е�����
	void setTimeLimit();//���� "������ʱʱ��" ��Ȩ��
	void paintEvent(QPaintEvent* event);//�滭
	bool isTimeLimitRight();//ʱ�����������Ƿ���ȷ
	bool isPassCityRight();//�ؾ������Ƿ���������յ�,�����Ƿ�̫��
	void printRoute();//��ӡ·��
	void analogAnimation();//ģ�⶯��
	void closeEvent(QCloseEvent* ev);//���ش��ڹر��¼�
	void printState(PassengerState state);//��ӡ״̬
private:
	Ui::TravelWindowClass ui;
	QCheckBox* selectPass_[CITYNUM];//CITYNUM��;������
	QPixmap backPix;//����
	QTimer* transTimer;//�û�ת��ʱ��Ķ�ʱ��
	QDateTime dateTime;//����ʱ�����
	QLabel* vehicle[4];//��ͨ����,��������
	QSequentialAnimationGroup* animations;//����Ⱥ
	TipWindow* tipWindow;//��ʾ��
};
