#pragma execution_character_set("utf-8")
#include "TravelWindow.h"
#include "Log.h"
#include <Windows.h>
TravelWindow::TravelWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1285, 800);//�̶����ڴ�СΪ ��1285 ��800
	tipWindow = new TipWindow;//��ʾ��
	/*-----------------------------��������-----------------------------*/
	for (unsigned int i = 0; i < 4; i++) {
		vehicle[i] = new QLabel(this);
		vehicle[i]->setFixedSize(34, 34);
		vehicle[i]->setScaledContents(true);
		vehicle[i]->hide();//������
	}
	QPixmap vehiclePic;
	vehiclePic.load(":/TravelWindow/bus");//���ؿͳ�ͼƬ
	vehicle[0]->setPixmap(vehiclePic);
	vehiclePic.load(":/TravelWindow/train");//���ػ�ͼƬ
	vehicle[1]->setPixmap(vehiclePic);
	vehiclePic.load(":/TravelWindow/airplan");//���طɻ�ͼƬ
	vehicle[2]->setPixmap(vehiclePic);
	vehiclePic.load(":/TravelWindow/wait");//���صȴ�ͼƬ
	vehicle[3]->setPixmap(vehiclePic);

	animations = new QSequentialAnimationGroup(this);
	/*----------------------------------�𰸿�����--------------------------------*/
	ui.answerEdit->setWordWrapMode(QTextOption::WordWrap);//���Զ�����
	ui.stateEdit->setWordWrapMode(QTextOption::WordWrap);//���Զ�����

	/*-------------------------------ѡ��;������UI-------------------------------*/
	for (unsigned int i = 0; i < CITYNUM; i++) {
		selectPass_[i] = new QCheckBox(this);
	}
	setCityNames();

	/*--------------"������ʱʱ��"��Ȩ������(ֻ����ѡ���������ʱ���������)-------------*/
	setTimeLimit();

	/*---------------------------------��ͼ����--------------------------------------*/
	backPix.load(":/TravelWindow/map");//���ص�ͼͼƬ

	/*--------------------------------��������---------------------------------------*/
	ui.stateButton->setEnabled(false);//��ʼ��ѯ��ť���ɵ��

	/*-------------------------------ʱ��������--------------------------------------*/
	transTimer = new QTimer(this);
	dateTime = dateTime.currentDateTime();//��ȡϵͳʱ��
	ui.startTime->setDateTime(dateTime);//��ʾ��ǰʱ��
	
	updateFile(dateTime.toString("#yyyy/MM/dd hh:mm:ss#").toStdString() 
		+ dateTime.toString(" #yyyy/MM/dd hh:mm:ss#").toStdString()
		+ " ����ϵͳ");//�û�����ϵͳʱ��

	connect(transTimer, &QTimer::timeout, this, [=]()mutable {
		dateTime = dateTime.addSecs(36 * PERSECONDHOURS);
		ui.startTime->setDateTime(dateTime);//��ʾ��ǰʱ��
	});
	transTimer->start(10);//1s->PERSECONDHOURS * 3600s 10ms->PERSECONDHOURS * 36s

	/*--------------------------------����·�߰�ť��Ӧ����-----------------------------*/

	connect(ui.startButton, &QPushButton::clicked, this, [=]()mutable {
		animations->stop();//ֹͣ�ϴζ���
		animations->clear();//ɾ���ϴζ���
		vehicle[3]->hide();
		ui.startButton->setEnabled(false);//δ�������ʱ�򲻿����ٵ�����·�߰�ť
		result.route.clear();//����ϴ�·��
		result.sumCost = 0;//�����ʱ
		result.sumTime = 0;//�����Ǯ
		update();//���ͼ��
		ui.answerEdit->clear();//���·�����ֿ�
		ui.sumCost->clear();//���ͳ��ʱ���
		ui.sumTime->clear();//���ͳ�ƽ�Ǯ��
		ui.stateEdit->clear();//���״̬���ֿ�
		ui.endTime->setDateTime(dateTime);//ˢ�µ���ʱ��(�տ�ʼ�ͳ���ʱ��һ��)

		QString tempStr = QDateTime::currentDateTime().toString("#yyyy/MM/dd hh:mm:ss#")
			+ dateTime.toString(" #yyyy/MM/dd hh:mm:ss#")
			+ QString(" �û���ѯ%1��%2��·��,��ȡ����%3").arg(cityInfoList[ui.startCity->currentIndex()].cityName.data())
			.arg(cityInfoList[ui.endCity->currentIndex()].cityName.data())
			.arg(ui.strategy->currentIndex() + 1);
		vector<int> passCities;//��ͣ����
		for (unsigned int i = 0; i < CITYNUM; i++) {	//��ȡ��ͣ����
			if (selectPass_[i]->isChecked() == true) {
				passCities.push_back(i);//���뵽��ͣ����vector
			}
		}
		if (passCities.size() == 0) {
			tempStr += QString(",δѡ��ؾ�����");
		}
		else {
			tempStr += QString(",ѡ��ıؾ�����Ϊ:");
			for (unsigned int i = 0; i < passCities.size(); i++) {
				tempStr += QString(cityInfoList[passCities[i]].cityName.data());
				tempStr += QString(" ");
			}
		}
		updateFile(tempStr.toStdString());

		if (ui.strategy->currentIndex() == 2) {	//ѡ�����������
			if (isTimeLimitRight() == false) {	//ʱ���������벻�Ϸ�
				ui.startButton->setEnabled(true);
				updateFile("����,ʱ�����Ʋ��Ϸ�");
				updateFile("-----------------------------------------------------------------------------");
				return;
			}
		}
		if (isPassCityRight() == false) {
			ui.startButton->setEnabled(true);
			updateFile("����,�ؾ�����ѡ�񲻺Ϸ�");
			updateFile("-----------------------------------------------------------------------------");
			return;
		}
		if (ui.startCity->currentIndex() == ui.endCity->currentIndex()) {
			ui.startButton->setEnabled(true);
			QMessageBox::critical(this, "����", "ʼ���غ�Ŀ�ĵز���һ��");
			updateFile("����,ʼ���غ�Ŀ�ĵ�ѡ���ظ�");
			updateFile("-----------------------------------------------------------------------------");
			return;
		}
		else {	//ʱ�����ƺϷ�,�ؾ�����ѡ��Ϸ�,�����غ�Ŀ�ĵز�ͬ
			transTimer->stop();//ֹͣ��ʱ
			QDateTime departureTime = dateTime;//��ȡ����ʱ��

			int strategyNum = ui.strategy->currentIndex();//��ȡ���Ա��
			int departureCity = ui.startCity->currentIndex();//��ȡ�������б��
			int destinatedCity = ui.endCity->currentIndex();//��ȡĿ�ĵس��б��
		
			//���濪ʼ����
			if (strategyNum == 0) {
				solveFirst(departureTime, departureCity, destinatedCity, passCities);
			}
			else if (strategyNum == 1) {
				solveSecond(departureTime, departureCity, destinatedCity, passCities);
			}
			else {
				tipWindow->show();
				int limitTime = ui.limitEdit->text().toInt();//��ȡ����ʱ��
				solveThird(departureTime, departureCity, destinatedCity, passCities, limitTime);
				tipWindow->hide();
			}
			if (result.route.size() > 0) {	//˵�����ڽ������
				printRoute();
				update();//ˢ�»���,��ͼ
				ui.stateButton->setEnabled(true);//���ڲ�ѯ��ť���Ե�
				ui.stateButton->setFocus();//���ý���
				analogAnimation();//���ö���
				transTimer->start(10);//��ʼ��ʱ
				QTimer::singleShot(result.sumTime * 1000 / PERSECONDHOURS, this, [=]() {
					vehicle[3]->move(cityInfoList[result.route[result.route.size() - 1].destination].cityPoint.x() - (vehicle[3]->width() / 2)
						,cityInfoList[result.route[result.route.size() - 1].destination].cityPoint.y() - (vehicle[3]->height() / 2));
					vehicle[3]->show();
					ui.stateEdit->setText("����Ŀ�ĵ�");
					ui.stateButton->setEnabled(false);//���� sumTime ʱ����ѯ��ť�����Ե�
					ui.startButton->setEnabled(true);//���� sumTime ʱ������ɰ�ť���Ե�
					updateFile("-----------------------------------------------------------------------------");
				});
				connect(ui.stateButton, &QPushButton::clicked, this, [=]() {
					QString tempStr = QDateTime::currentDateTime().toString("# yyyy/MM/dd hh:mm:ss #")
						+ dateTime.toString(" #yyyy/MM/dd hh:mm:ss#")
						+ QString(" �û���ѯ��ǰ״̬");
					updateFile(tempStr.toStdString());
					PassengerState state = currentState(dateTime);//���뵱ǰʱ��
					//�����Ȳ���ͣ��,��Ϊ��ľ޿�
					printState(state);//��ӡ״̬
				});
			}
			else {
				updateFile("������Ҫ���޽������");
				updateFile("-----------------------------------------------------------------------------");
				QMessageBox::critical(this, "����", "��Ǹ,����������ڽ������");
				transTimer->start();//������ʱ
				ui.stateButton->setEnabled(false);//��ѯ��ť�����Ե�
				ui.startButton->setEnabled(true);//���ɰ�ť���Ե�
			}
		}
	});
}

void TravelWindow::printRoute()
{
	QDateTime arrivalTime = result.departureTime.addSecs(result.sumTime * 3600);
	ui.endTime->setDateTime(arrivalTime);//��ʾ����ʱ��
	ui.sumTime->setText(QString("%1Сʱ").arg(result.sumTime));//��ʾ��ʱ
	ui.sumCost->setText(QString("%1Ԫ").arg(result.sumCost));//��ʾ����
	QString tempStr;
	QString start;//��ʼ����
	QString end;//Ŀ�ĳ���
	QString type;//��ͨ��������
	QDateTime currentTime = result.departureTime;//��ǰʱ��
	
	for (unsigned int i = 0; i < result.route.size(); i++) {
		start = cityInfoList[result.route[i].origin].cityName.data();//��ʼ����
		end = cityInfoList[result.route[i].destination].cityName.data();//Ŀ�ĳ���
		switch (result.route[i].trafficType) {
			case 0: {
				type = "����";
				break;
			}
			case 1: {
				type = "��";
				break;
			}
			default: {
				type = "�ɻ�";
				break;
			}
		}//��ȡ��ͨ��ʽ
		if (i == 0) {	//�յ���վ
			QString final = cityInfoList[result.route[result.route.size() - 1].destination].cityName.data();//����Ŀ�ĵ�
			tempStr = QString("[%1] ��%2׼������ǰ��%3").arg(currentTime.toString("yyyy/MM/dd hhʱ")).arg(start)
				.arg(final);
			ui.answerEdit->append(tempStr);
			updateFile(tempStr.toStdString());
		}
		
		int waitTime = result.route[i].departureTime - currentTime.time().hour();
		if (waitTime < 0) {	//�����
			waitTime += 24;
		}
		currentTime = currentTime.addSecs(waitTime * 3600);
		tempStr = QString("[%1] ��%2����%3��").arg(currentTime.toString("yyyy/MM/dd hhʱ")).arg(start).arg(result.route[i].trafficName.data())
			+ type + QString("ǰ��%1").arg(end);
		ui.answerEdit->append(tempStr);
		updateFile(tempStr.toStdString());
		int moveTime = result.route[i].arrivalTime - result.route[i].departureTime;
		if (moveTime < 0) {
			moveTime += 24;
		}
		currentTime = currentTime.addSecs(moveTime * 3600);//���ൽ��ʱ��
		tempStr = QString("[%1] ����%2").arg(currentTime.toString("yyyy/MM/dd hhʱ")).arg(end);
		ui.answerEdit->append(tempStr);
		updateFile(tempStr.toStdString());
	}
}

void TravelWindow::setCityNames()//Ϊѡ��;�����и�����ť�����ϳ��е�����
{
	unsigned int x = ui.selectLabel->x() + 10;
	unsigned int y = ui.selectLabel->y() + 8;
	for (unsigned int i = 0; i < CITYNUM; i++) {
		selectPass_[i]->move(x, y);
		if ((i + 1) % 3 == 0 && i != 0) {
			y += 30;
			x = ui.selectLabel->x() + 10;
		}
		else {
			x += 100;
		}
	}
	selectPass_[0]->setText("����");
	selectPass_[1]->setText("�Ϻ�");
	selectPass_[2]->setText("������");
	selectPass_[3]->setText("����");
	selectPass_[4]->setText("����");
	selectPass_[5]->setText("����");
	selectPass_[6]->setText("֣��");
	selectPass_[7]->setText("�Ͼ�");
	selectPass_[8]->setText("��ɳ");
	selectPass_[9]->setText("���ͺ���");
	selectPass_[10]->setText("�ɶ�");
	selectPass_[11]->setText("�人");
}

void TravelWindow::setTimeLimit()//"������ʱʱ��"��Ȩ������(ֻ����ѡ���������ʱ���������)
{
	ui.limitEdit->setMaxLength(3);//�Ϊ999Сʱ
	ui.limitEdit->setReadOnly(true);//Ĭ������Ϊֻ��
	ui.limitEdit->setPlaceholderText("��������");//Ĭ����ʾ��������
	connect(ui.strategy, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, [=](int index) {
		if (index == 2) {	//���ѡ����ǵ���������
			ui.limitEdit->setPlaceholderText("����,��λ:Сʱ");//Ĭ����ʾ���
			ui.limitEdit->setReadOnly(false);//��д
			ui.limitEdit->setFocus();//�Զ���λ��굽�༭��
		}
		else {
			ui.limitEdit->clear();//����༭���е�����
			ui.limitEdit->setReadOnly(true);//����Ϊֻ��
			ui.limitEdit->setPlaceholderText("��������");//Ĭ����ʾ��������
		}
	});
}


void TravelWindow::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	QRect mapRect(ui.mapLabel->x(), ui.mapLabel->y(), ui.mapLabel->width(), ui.mapLabel->height());
	painter.drawPixmap(mapRect, backPix);
	QPen pen;
	pen.setColor(QColor("red"));
	pen.setWidth(3);//�ʿ�Ϊ5
	painter.setPen(pen);//�󶨱�
	if (result.route.size() > 0) {
		QPoint start;
		QPoint end;
		for (unsigned int i = 0; i < result.route.size(); i++) {
			start = cityInfoList[result.route[i].origin].cityPoint;
			end = cityInfoList[result.route[i].destination].cityPoint;
			painter.drawLine(start, end);
		}
		//����Ѿ����ĵ��ɫ
		pen.setWidth(15);
		painter.setPen(pen);
		for (unsigned int i = 0; i < result.route.size(); i++) {
			painter.drawPoint(cityInfoList[result.route[i].origin].cityPoint);
			if (i == result.route.size() - 1) {
				painter.drawPoint(cityInfoList[result.route[i].destination].cityPoint);
			}
		}
	}
}

bool TravelWindow::isTimeLimitRight()
{
	QString timeLimit = ui.limitEdit->text();
	if (timeLimit.isEmpty() == true) {	//δ����
		QMessageBox::critical(this, "����", "������ʱ������");
		return false;
	}
	else {	//����,�ж������Ƿ���ȷ(������)
		for (unsigned int i = 0; i < timeLimit.size(); i++) {
			if (timeLimit[i] > '9' || timeLimit[i] < '0') {
				QMessageBox::critical(this, "����", "ʱ����������������");
				return false;
			}
		}
		return true;
	}
}

bool TravelWindow::isPassCityRight()
{
	int count = 0;
	for (unsigned int i = 0; i < CITYNUM; i++) {
		if (selectPass_[i]->isChecked() == true) {	//��ѡ��
			if (i == ui.startCity->currentIndex() || i == ui.endCity->currentIndex()) {
				QMessageBox::critical(this, "����", "�ؾ����в���ѡ�������յ�");
				return false;
			}
			else {
				count++;
				if (count > MAXPASSCITY) {
					QMessageBox::critical(this, "����", QString("�ؾ��������ѡ��%1��").arg(MAXPASSCITY));
					return false;
				}
			}
		}
	}
	return true;
}

void TravelWindow::analogAnimation()
{
	//���ж���
	QPropertyAnimation* perAnimation = nullptr;
	int waitTime = 0;
	int moveTime = 0;
	QPoint start;
	QPoint end;
	for (unsigned int i = 0; i < result.route.size(); i++) {
		//��ȴ�ʱ��
		if (i == 0) {	//��һ�˺���
			waitTime = result.route[i].departureTime - result.departureTime.time().hour();
			if (waitTime < 0) {
				waitTime += 24;
			}
		}
		else {
			waitTime = result.route[i].departureTime - result.route[i - 1].arrivalTime;//�˺��෢��ʱ��-�ϴκ��ൽ��ʱ��
			if (waitTime < 0) {
				waitTime += 24;
			}
		}
		//�����ȴ�����
		perAnimation = new QPropertyAnimation(vehicle[3], "pos",this);
		perAnimation->setDuration(waitTime * 1000 / PERSECONDHOURS);//ת���ɺ���
		start = QPoint(cityInfoList[result.route[i].origin].cityPoint.x() - (vehicle[3]->width() / 2),
			cityInfoList[result.route[i].origin].cityPoint.y() - (vehicle[3]->height() / 2));
		end = QPoint(cityInfoList[result.route[i].origin].cityPoint.x() - (vehicle[3]->width() / 2),
			cityInfoList[result.route[i].origin].cityPoint.y() - (vehicle[3]->height() / 2));
		perAnimation->setStartValue(start);//������ʼ����
		perAnimation->setEndValue(end);//������������
		//��ʼ����ͽ�������һ��,����ȴ�
		animations->addAnimation(perAnimation);
		connect(perAnimation, &QAbstractAnimation::stateChanged, this, [=](int newState, int oldState) {
			if (newState == 2 && oldState == 0) {	//������stopתΪrun,��ʾͼƬ
				vehicle[3]->show();
			}
			else if (newState == 0 && oldState == 2) {	//������runתΪstop,����ͼƬ
				vehicle[3]->hide();
			}
		});
		//���ƶ�ʱ��
		moveTime =  result.route[i].arrivalTime - result.route[i].departureTime;//����ʱ���ȥ����ʱ��
		if (moveTime <= 0) {
			moveTime += 24;
		}
		perAnimation = new QPropertyAnimation(vehicle[result.route[i].trafficType], "pos",this);
		perAnimation->setDuration(moveTime * 1000 / PERSECONDHOURS);//ת���ɺ���
		start = QPoint(cityInfoList[result.route[i].origin].cityPoint.x() - (vehicle[result.route[i].trafficType]->width() / 2),
			cityInfoList[result.route[i].origin].cityPoint.y() - (vehicle[result.route[i].trafficType]->height() / 2));
		end = QPoint(cityInfoList[result.route[i].destination].cityPoint.x() - (vehicle[result.route[i].trafficType]->width() / 2),
			cityInfoList[result.route[i].destination].cityPoint.y() - (vehicle[result.route[i].trafficType]->height() / 2));
		perAnimation->setStartValue(start);//������ʼ����
		perAnimation->setEndValue(end);//������������
		animations->addAnimation(perAnimation);
		connect(perAnimation, &QAbstractAnimation::stateChanged, this, [=](int newState, int oldState) {
			if (newState == 2 && oldState == 0) {	//������stopתΪrun,��ʾͼƬ
				vehicle[result.route[i].trafficType]->show();
			}
			else if (newState == 0 && oldState == 2) {	//������runתΪstop,����ͼƬ
				vehicle[result.route[i].trafficType]->hide();
			}
		});
	}
	animations->start();
}


void TravelWindow::printState(PassengerState state)
{
	ui.stateEdit->clear();//�����һ�ε�״̬��ӡ
	if (state.isMoving == false) {	//�ڳ�վ�ȳ�
		QString tempStr = QString("��%1վ�ȴ�").arg(cityInfoList[state.cityNumber].cityName.data());
		ui.stateEdit->append(tempStr);
		updateFile(tempStr.toStdString());
	}
	else {
		QString type;//��ͨ��������
		switch (state.routeInfo.trafficType) {
		case 0: {
			type = "������";
			break;
		}
		case 1: {
			type = "����";
			break;
		}
		default: {
			type = "�ɻ���";
			break;
		}
		}
		QString tempStr = QString("�ڴ�%1ǰ��%2��%3��").arg(cityInfoList[state.routeInfo.origin].cityName.data())
			.arg(cityInfoList[state.routeInfo.destination].cityName.data())
			.arg(state.routeInfo.trafficName.data()) + type;
		ui.stateEdit->append(tempStr);
		updateFile(tempStr.toStdString());

	}
}


void TravelWindow::closeEvent(QCloseEvent* ev)
{
	animations->stop();
	animations->clear();
	delete tipWindow;
	updateFile(QDateTime::currentDateTime().toString("#yyyy/MM/dd hh:mm:ss#").toStdString() 
		+ dateTime.toString(" #yyyy/MM/dd hh:mm:ss#").toStdString()
		+ " �˳�ϵͳ");
	updateFile("******************************************************************************");
	logFile.close();
}