#include "TimeTable.h"

vector<TrafficInfo> timeTable;//���� �г�ʱ�̱�
vector<CityInfo> cityInfoList;//���� ������Ϣ(���,����,����)

void readFromFile()
{
	makeCityList();//�������б�

	fstream file;
	file.open("traffic.txt", ios::in);//ֻ����ʽ���ļ�
	if (file.is_open() == false) {	//�ļ���ʧ��
		exit(0);//�˳�
	}
	
	TrafficInfo tempInfo;
	string tempStr;
	int tempInt;
	while (file >> tempStr) {
		tempInfo.origin = cityToNumber(tempStr);//ʼ����
		file >> tempStr;
		tempInfo.destination = cityToNumber(tempStr);//Ŀ�ĵ�
		file >> tempStr;
		tempInfo.trafficName = tempStr;
		file >> tempInt;
		tempInfo.departureTime = tempInt;//����ʱ��
		file >> tempInt;
		tempInfo.arrivalTime = tempInt;//����ʱ��
		file >> tempInt;
		tempInfo.cost = tempInt;//����
		file >> tempInt;
		tempInfo.trafficType = tempInt;//��ͨ��������

		timeTable.push_back(tempInfo);//���뵽timeTable��
	}
	file.close();
}

void makeCityList()
{
	//�Ȳ�������
	CityInfo temp;

	temp.cityName = "Beijing";
	temp.cityPoint = QPoint(718, 305);
	cityInfoList.push_back(temp);

	temp.cityName = "Shanghai";
	temp.cityPoint = QPoint(820, 499);
	cityInfoList.push_back(temp);

	temp.cityName = "Harbin";
	temp.cityPoint = QPoint(856, 150);
	cityInfoList.push_back(temp);

	temp.cityName = "Kunming";
	temp.cityPoint = QPoint(477, 647);
	cityInfoList.push_back(temp);

	temp.cityName = "Lhasa";
	temp.cityPoint = QPoint(271, 525);
	cityInfoList.push_back(temp);

	temp.cityName = "Haikou";
	temp.cityPoint = QPoint(634, 757);
	cityInfoList.push_back(temp);

	temp.cityName = "Zhengzhou";
	temp.cityPoint = QPoint(684, 433);
	cityInfoList.push_back(temp);

	temp.cityName = "Nanjing";
	temp.cityPoint = QPoint(783, 477);
	cityInfoList.push_back(temp);

	temp.cityName = "Changsha";
	temp.cityPoint = QPoint(674, 568);
	cityInfoList.push_back(temp);

	temp.cityName = "Huhhot";
	temp.cityPoint = QPoint(634, 301);
	cityInfoList.push_back(temp);

	temp.cityName = "Chengdu";
	temp.cityPoint = QPoint(512, 528);
	cityInfoList.push_back(temp);

	temp.cityName = "Wuhan";
	temp.cityPoint = QPoint(698, 530);
	cityInfoList.push_back(temp);
}

int cityToNumber(string cityName)
{
	for (unsigned int i = 0; i < cityInfoList.size(); i++) {
		if (cityName == cityInfoList[i].cityName) {
			return i;
		}
	}
}