#pragma once
#include "TimeTable.h"
#include <QDateTime>
#include <algorithm>

#define MAXDEPTH 6//�ݹ����
struct PassengerState {
	bool isMoving;//�Ƿ���·��
	TrafficInfo routeInfo;//�����·��,·����Ϣ
	int cityNumber;//�����ĳ������ͣ��,ͣ��������Ϣ
};//�˿�״̬�ṹ��

struct Result {
	vector<TrafficInfo> route;//�ɸ�������(����)��ɵ�·��
	QDateTime departureTime;//����ʱ��
	int sumTime = 0;//����ʱ
	int sumCost = 0;//�ܷ���
};

struct MinTime {
	int spendTime;//��A�ص�B�ص����ʱ��,�����ȳ�ʱ��
	int index;//��A�ص�B�ص����ʱ������Ӧ�ĳ���
	int arriveTime;//����B�ص�ʱ��
};

extern Result result;//���� ���

void makeMatrix();
/*
	����:�����ڽӾ���
*/
void solveFirst(QDateTime departureTime, int departureCity, int destinatedCity, vector<int> passCities);
/*
	����:���"��������"����
	departureTime ����ʱ��
	departureCity �������б��
	destinatedCity Ŀ�ĳ��б��
	passCities ��ͣ������
*/
void solveSecond(QDateTime departureTime, int departureCity, int destinatedCity, vector<int> passCities);
/*
	����:�����ʱ�����١�����
	departureTime ����ʱ��
	departureCity �������б��
	destinatedCity Ŀ�ĳ��б��
	passCities ��ͣ������
*/
void solveThird(QDateTime departureTime, int departureCity, int destinatedCity, vector<int> passCities, int limitTime);
/*
	����:�������ʱʱ��,�������١�����
	departureTime ����ʱ��
	departureCity �������б��
	destinatedCity Ŀ�ĳ��б��
	passCities ��ͣ������
	limitTime ��ʱʱ��
*/
Result dijkstra(int departureTime, int departureCity, int destinatedCity);
/*
	����:�����������غͳ���ʱ��,�������·��,��solveSecond����,��������ڶ�������
	departureTime ����ʱ��
	departureCity ʼ����
	destinatedCity Ŀ�ĵ�
*/
MinTime findMinTime(int startTime, int departureCity, int destinatedCity);
/*
	�˺�������Ѱ������֮��ķ�ʱ�����ٵĽ�ͨ��ʽ����ķѵ�ʱ��,��dijkstra����,��������ڶ�������
	startTime ����ʱ��
	departureCity ��������
	destinatedCity �������
*/
vector<TrafficInfo> makeRouteTable(int strategyNum,int path[],MinTime time[],int departureCity, int destinatedCity);
/*
	����:Ϊ��һ�ֺ͵ڶ��ֽ����������·�߱�,·�߱���һ�����������
	strategyNum ���Ժ�
	path һά����,ǰ��·��(���ڵ�һ�ֲ���)
	time һά����,����MinTime�е�index,ȷ������֮�佻ͨ��ʽ(���ڵڶ��ֲ���)
	departureCity ��ʼ��
	destinatedCity Ŀ�ĵ�
*/
int calculateTime(Result result);
/*
	����:����result������ʱ��
*/
void permutate(vector<vector<int>>& permResult, vector<int>& passCities, int begin);
/*
	����:����ؾ����е�ȫ����
	permResult ȫ���к�Ľ��,��ά����
	passCities �ؾ������� һά����
	begin �����ݹ�,Ĭ��Ϊ0,passCities��һ��Ԫ��
*/
void DFS(TrafficInfo preTraffic, int spendTime, vector<TrafficInfo>& tempResult, Result& finalResult
	,int destinatedCity,int limitTime,int depth,int& maxCost, vector<int>&passCities,int spendCost);
/*
	����:���û��ݷ�,�������������
	���ݵ�����Ϊ:
	1.���ѵ�ʱ���������ʱ��
	2.���ѵĽ�Ǯ����"��ǰ���·��"�Ľ�Ǯ
	3.�ݹ���ȴ���MAXDEPTH

	preTraffic ��һ�εݹ��������������·��,�����жϴ˴εݹ���õ� ��������,�Ϳ�ʼʱ��
	spendTime �������õݹ鿪ʼ���������õ���ʱ��,�ж��Ƿ��Ѿ���Խʱ������
	tempResult ���ٵ���·��,ÿ�ݹ�һ���push_backһ������,ÿ����һ��ݹ��pop_back
	finalResult �ڵݹ������,ÿ�λ��һ�����õ�·��,�����finalResult
	destinatedCity ����Ҫ�����Ŀ�ĵ�
	limitTime ����ʱ��,���ڼ�֦
	depth �ݹ����,���ڼ�֦
	maxCost ��ǰ��õ�·���Ļ���,���ڼ�֦
	passCities �ؾ��ĳ���
	spendCost  �����ݹ���ÿ�ʼ���������õ��ܷ���,�ж��Ƿ��Ѿ���ԽmaxCost
*/
bool isHasPass(vector<TrafficInfo>& tempResult, vector<int>&passCities);
/*
	����:�ж�һ��·���Ƿ�����ؾ�����,��DFS����,�����ж��Ƿ����finalResult
	tempResult ·��
	passCities �Ͼ�����
*/
PassengerState currentState(QDateTime pressTime);
/*
	����:�����˿͵�ǰ״̬
	pressTime �����ѯ��ťʱ������ʱ��
	����ֵΪ�˿͵�ǰ״̬�ṹ��
*/