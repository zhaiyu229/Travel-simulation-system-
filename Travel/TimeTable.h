#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <QPoint>
using namespace std;
#define CITYNUM 12
#define MAXCOST 100000

struct TrafficInfo {
	int origin = -1;//��(����)����ʼ����
	int destination = -1;//��(����)����Ŀ�ĵ�
	string trafficName = "Noon";//��ͨ���ߵľ������� G9003
	int departureTime;//����ʱ��,��ȷ��Сʱ
	int arrivalTime;//����ʱ��,��ȷ��Сʱ
	int cost;//�˳��λ��Ѷ���Ǯ
	int trafficType;//��ͨ���ߵ�����	0->���� 1->�� 2->�ɻ�
};

struct CityInfo {
	string cityName;//��������
	QPoint cityPoint;//��������
};
//���б��(vector�±������),����,����

extern vector<CityInfo> cityInfoList;//vector�е��±������б��
extern vector<TrafficInfo> timeTable;//���� �г�ʱ�̱�

void readFromFile();//���ļ���ȡ�����ε���Ϣ
void makeCityList();//���ɳ�����Ϣ��
int cityToNumber(string cityName);
/*
	����:�ѳ���ת��Ϊ��Ӧ�ı��
	cityName ��������
*/