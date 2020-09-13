#include "Solution.h"
#include <qDebug>
static vector<TrafficInfo> allAdjMatrix[CITYNUM][CITYNUM];//�������г���(����)��Ϣ���ڽӾ���
static TrafficInfo firstAdjMatrix[CITYNUM][CITYNUM];//ֻ��������֮������˽�ͨ��ʽ���ڽӾ���
Result result;//���� ���

void makeMatrix()
{
	/*
		allAdjMatrix[i][j]����vector��sizeΪ0,˵�� i �ص� j �� ���г�
		firstAdjMatrix[i][j]����cost ΪMAXCOST,˵�� i �ص� j �� ���г�
	*/

	int start, end;//ʼ���� Ŀ�ĵ�
	TrafficInfo temp;
	temp.cost = MAXCOST;
	for (unsigned int i = 0; i < CITYNUM; i++) {
		for (unsigned int j = 0; j < CITYNUM; j++) {
			firstAdjMatrix[i][j] = temp;//��ʼ����һ�ֲ��Ե��ڽӾ���
		}
	}

	for (unsigned int i = 0; i < timeTable.size(); i++) {
		start = timeTable[i].origin;//ʼ����
		end = timeTable[i].destination;//Ŀ�ĵ�
		allAdjMatrix[start][end].push_back(timeTable[i]);//���뵽allAdjMatrix[start][end]��vector��
		if (timeTable[i].cost < firstAdjMatrix[start][end].cost) {	//����˻��ѽ�С,�滻��ǰ��ͨ��ʽ
			firstAdjMatrix[start][end] = timeTable[i];
		}
	}

}

void solveFirst(QDateTime departureTime, int departureCity, int destinatedCity, vector<int> passCities)
{
	//���������㷨
	unsigned int cost[CITYNUM][CITYNUM];//����֮����С����
	int path[CITYNUM][CITYNUM];//���·����¼

	for (unsigned int i = 0; i < CITYNUM; i++) {
		for (unsigned j = 0; j < CITYNUM; j++) {
			cost[i][j] = firstAdjMatrix[i][j].cost;
			if (cost[i][j] < MAXCOST && i != j) {	//i->j �л�
				path[i][j] = i;//j��ǰ��Ϊi
			}
			else {
				path[i][j] = -1;//i->j�޻�
			}
		}
	}
	for (unsigned int k = 0; k < CITYNUM; k++) {
		for (unsigned int i = 0; i < CITYNUM; i++) {
			for (unsigned int j = 0; j < CITYNUM; j++) {
				if (cost[i][k] + cost[k][j] < cost[i][j]) {	//i->j�Ļ��Ѵ���i->k->j�Ļ���
					cost[i][j] = cost[i][k] + cost[k][j];
					path[i][j] = path[k][j];//j��ǰ����Ϊi
				}
			}
		}
	}

	if (passCities.size() > 0) {	//ѡ����;������
		vector<vector<int>> permResult;//����ȫ���н��
		permutate(permResult, passCities, 0);//ȫ����
		//�������ʼ�غ�Ŀ�ĵؼ��뵽ȫ������,���������·��
		for (unsigned int i = 0; i < permResult.size(); i++) {
			permResult[i].insert(permResult[i].begin(), departureCity);//��ͷ��������ʼ��
			permResult[i].push_back(destinatedCity);//��β������Ŀ�ĵ�
		}

		unsigned int minCostIndex = 0;//��С���÷�����n!�������еı��
		unsigned int minCost = INT_MAX;//��С����
		unsigned int start;//��ʼ��
		unsigned int end;//Ŀ�ĵ�

		//ѡȡ���Ų���
		for (unsigned int i = 0; i < permResult.size(); i++) {
			unsigned int realCost = 0;//ÿ��������ʵ�ʻ���
			for (unsigned int j = 0; j < permResult[i].size() - 1; j++) {
				start = permResult[i][j];//������ʼ��
				end = permResult[i][j + 1];//����Ŀ�ĵ�
				realCost += cost[start][end];//���λ���			         
			}
			if (realCost < minCost) {
				minCost = realCost;
				minCostIndex = i;
			}
		}

		//minCostIndex��Ϊ������Ĳ���,������Ҫƴ��
		vector<TrafficInfo> directRoute;//��ɢ��·��
		MinTime time[CITYNUM];//����
		for (unsigned int i = 0; i < permResult[minCostIndex].size() - 1; i++) {
			start = permResult[minCostIndex][i];//������ʼ��
			end = permResult[minCostIndex][i + 1];//����Ŀ�ĵ�
			directRoute = makeRouteTable(0, path[start], time, start, end);//��ȡ���κ����
			result.route.insert(result.route.end(), directRoute.begin(), directRoute.end());//���뵽���������·�߱���
		}

		result.sumCost = minCost;//�ܻ���
		result.departureTime = departureTime;//ʵ�ʳ���ʱ��(���ǵ�һ������ĳ���ʱ��)
	}
	else {	//δѡ��ؾ�����
		MinTime time[CITYNUM];//����
		result.route = makeRouteTable(0, path[departureCity], time, departureCity, destinatedCity);
		result.sumCost = cost[departureCity][destinatedCity];//�ܷ���
		result.departureTime = departureTime;//ʵ�ʳ���ʱ��(���ǵ�һ������ĳ���ʱ��)
	}

	result.sumTime = calculateTime(result);//����ʱ��

}

void solveSecond(QDateTime departureTime, int departureCity, int destinatedCity, vector<int> passCities)
{
	if (passCities.size() > 0) {
		vector<vector<int>> permResult;//����ȫ���н��
		permutate(permResult, passCities, 0);//ȫ����
		//�������ʼ�غ�Ŀ�ĵؼ��뵽ȫ������,���������·��
		for (unsigned int i = 0; i < permResult.size(); i++) {
			permResult[i].insert(permResult[i].begin(), departureCity);//��ͷ��������ʼ��
			permResult[i].push_back(destinatedCity);//��β������Ŀ�ĵ�
		}

		unsigned int minTimeIndex = 0;//��Сʱ�䷽����n!�������еı��
		unsigned int minTime = INT_MAX;//��Сʱ��
		unsigned int start;//��ʼ��
		unsigned int end;//Ŀ�ĵ�
		int  directStartTime = 0;
		for (unsigned int i = 0; i < permResult.size(); i++) {	//ÿһ�ַ���
			directStartTime = departureTime.time().hour();//ÿ��·���Ŀ�ʼʱ��
			Result tempResult;
			unsigned int realTime = 0;//ÿ��������ʵ��ʱ��
			for (unsigned int j = 0; j < permResult[i].size() - 1; j++) {
				start = permResult[i][j];//������ʼ��
				end = permResult[i][j + 1];//����Ŀ�ĵ�
				tempResult = dijkstra(directStartTime, start, end);//���汾�ν��
				directStartTime = tempResult.route[tempResult.route.size() - 1].arrivalTime;//���¿�ʼʱ��
				realTime += tempResult.sumTime;//�ۼ���ʱ��
			}
			if (realTime < minTime) {
				minTime = realTime;
				minTimeIndex = i;
			}
		}
		//minTimeIndex��Ϊ������Ĳ���,������Ҫƴ��
		vector<TrafficInfo> directRoute;//��ɢ��·��
		directStartTime = departureTime.time().hour();//ÿ��·���Ŀ�ʼʱ��
		for (unsigned int i = 0; i < permResult[minTimeIndex].size() - 1; i++) {
			start = permResult[minTimeIndex][i];//������ʼ��
			end = permResult[minTimeIndex][i + 1];//����Ŀ�ĵ�
			directRoute = dijkstra(directStartTime, start, end).route;//��ȡ���κ����
			directStartTime = directRoute[directRoute.size() - 1].arrivalTime;//���³���ʱ��
			result.route.insert(result.route.end(), directRoute.begin(), directRoute.end());//���뵽���������·�߱���
		}

		//�����
		for (unsigned int i = 0; i < result.route.size(); i++) {
			result.sumCost += result.route[i].cost;
		}
		result.departureTime = departureTime;//ʵ�ʳ���ʱ��(���ǵ�һ������ĳ���ʱ��)
		result.sumTime = minTime;
	}
	else {	//δѡ��;������
		result = dijkstra(departureTime.time().hour(), departureCity, destinatedCity);
		//�����
		for (unsigned int i = 0; i < result.route.size(); i++) {
			result.sumCost += result.route[i].cost;
		}
		result.departureTime = departureTime;//ʵ�ʳ���ʱ��(���ǵ�һ������ĳ���ʱ��)
	}
}

void solveThird(QDateTime departureTime, int departureCity, int destinatedCity, vector<int> passCities, int limitTime)
{
	solveFirst(departureTime, departureCity, destinatedCity, passCities);
	if (result.sumTime > limitTime) {	//��С���ò���������ʱ��
		result.departureTime = departureTime;
		result.route.clear();
		result.sumCost = 0;
		result.sumTime = 0;
		solveSecond(departureTime, departureCity, destinatedCity, passCities);
		if (result.sumTime > limitTime) {	//��Сʱ�䶼��������ʱ����˵����·��
			result.departureTime = departureTime;
			result.route.clear();
			result.sumCost = 0;
			result.sumTime = 0;
		}
		else {
			int maxCost = result.sumCost;//����ǰ����·�������ѵĽ�Ǯ,����·��ָ�������޶�ʱ����,��Ǯ�������ٵ�·��
			result.departureTime = departureTime;
			result.route.clear();
			result.sumCost = 0;
			result.sumTime = 0;
			vector<TrafficInfo> tempResult;//���ٵ���·��
			Result finalResult;//����ǰ�����·��
			int spendTime = 0;//��ǰ���ѵ�ʱ��
			int depth = 0;//��ǰ�ݹ����
			int spendCost = 0;//��ǰ���ѽ�Ǯ
			for (unsigned int i = 0; i < CITYNUM; i++) {	//���Դ�depatureCityǰ����һ������
				if (i != departureCity) {
					for (unsigned int j = 0; j < allAdjMatrix[departureCity][i].size(); j++) {//depatureCityǰ����һ�����е����н�ͨ��ʽ
							//����spendTime
						int waitTime = allAdjMatrix[departureCity][i][j].departureTime - departureTime.time().hour();
						if (waitTime < 0) {
							waitTime += 24;
						}
						int moveTime = allAdjMatrix[departureCity][i][j].arrivalTime
							- allAdjMatrix[departureCity][i][j].departureTime;
						if (moveTime < 0) {
							moveTime += 24;
						}
						spendTime += waitTime;
						spendTime += moveTime;
						//��spendCost
						spendCost += allAdjMatrix[departureCity][i][j].cost;
						//���˺���push_back��tempResult
						tempResult.push_back(allAdjMatrix[departureCity][i][j]);
						//����DFS
						DFS(allAdjMatrix[departureCity][i][j], spendTime, tempResult,
							finalResult, destinatedCity, limitTime, depth++, maxCost, passCities, spendCost);
						tempResult.pop_back();//�Ժ��࿪ʼ��·�ߵݹ����,����pop_back��ȥ������һ�εݹ�
						depth--;//���غ� �ݹ���ȼ�һ
						spendTime -= waitTime;//����ʱ��ָ�
						spendTime -= moveTime;//����ʱ��ָ�
						spendCost -= allAdjMatrix[departureCity][i][j].cost;//���ѽ�Ǯ�ָ�
					}
				}
			}
			result = finalResult;
			result.departureTime = departureTime;
		}
	}	
}

Result dijkstra(int departureTime, int departureCity, int destinatedCity)
{
	bool isJoin[CITYNUM];//������ĵ�ļ���
	MinTime time[CITYNUM];// ���ѵ�ʱ�� ���ð�α�� �����ʱ��
	int path[CITYNUM];//���ɵ�ǰ��·��
	unsigned int MAXTIME = SHRT_MAX;//���ʱ��
	for (unsigned int i = 0; i < CITYNUM; i++) {
		isJoin[i] = false;//����Դ�㶼û����
		if (i != departureCity) {
			time[i] = findMinTime(departureTime, departureCity, i); //ȷ��Դ�㵽ĳ�����Ƿ���ֱ��·�� ȷ����ͨ��ʽ

			if (time[i].spendTime < MAXTIME) {
				path[i] = departureCity;
			}
			else {
				path[i] = -1;//��ֱ��·��
			}
		}
	}

	isJoin[departureCity] = true;//��Դ����뼯��
	//time[departureCity].spendTime = 0;
	//��ʼ������

	for (unsigned int i = 0; i < CITYNUM - 1; i++) {	//i����ѭ��,������ CITYNUM - 1��ѭ����ʣ��CITYNUM - 1�����мӽ���
		unsigned int minTime = SHRT_MAX;
		int joinCity;
		for (unsigned int j = 0; j < CITYNUM; j++) {
			if (isJoin[j] == false && time[j].spendTime < minTime) {
				joinCity = j;
				minTime = time[j].spendTime;
			}
		}
		isJoin[joinCity] = true;//���˵�������
		for (unsigned int j = 0; j < CITYNUM; j++) {	//����
			if (isJoin[j] == false) {	//���Ǽ����еĵ�
				MinTime temp = findMinTime(time[joinCity].arriveTime, joinCity, j);//Ѱ�Ҵ˵㵽j�������ʱ�估�佻ͨ��ʽ
				if (time[joinCity].spendTime + temp.spendTime < time[j].spendTime) {
					time[j].spendTime = time[joinCity].spendTime + temp.spendTime;//����ʱ��
					time[j].index = temp.index;//��ȡ����,�������ĳ���
					time[j].arriveTime = temp.arriveTime;
					path[j] = joinCity;//����ǰ��
				}
			}
		}
	}
	Result tempResult;
	tempResult.route = makeRouteTable(1, path, time, departureCity, destinatedCity);
	QDateTime tempDateTime;
	tempDateTime.setTime(QTime(departureTime, 0));
	tempResult.departureTime = tempDateTime;

	//qDebug() << tempDateTime.time().hour() << endl;

	tempResult.sumTime = calculateTime(tempResult);//���㱾��ʱ��
	return tempResult;
}

MinTime findMinTime(int startTime, int departureCity, int destinatedCity)
{
	MinTime time;
	unsigned int minTime = SHRT_MAX;
	unsigned int minTimeIndex = 0;
	for (int i = 0; i < allAdjMatrix[departureCity][destinatedCity].size(); i++) {
		int waitTime = 0;
		int moveTime = 0;
		int realTime = 0;
		waitTime = allAdjMatrix[departureCity][destinatedCity][i].departureTime - startTime;
		if (waitTime < 0) {
			waitTime += 24;
		}
		moveTime = allAdjMatrix[departureCity][destinatedCity][i].arrivalTime
			- allAdjMatrix[departureCity][destinatedCity][i].departureTime;//����ʱ���ȥ����ʱ��
		if (moveTime < 0) {
			moveTime += 24;
		}
		realTime += waitTime;//ʱ���ۼ�
		realTime += moveTime;//ʱ���ۼ�
		if (realTime < minTime) {
			minTime = realTime;
			minTimeIndex = i;
		}
	}

	time.spendTime = minTime;
	//����Ҫ���жϵ�...
	//��Ϊ�п�������֮����ֱ���г�
	//��ôallAdjMatrix[departureCity][destinatedCity][minTimeIndex]����Խ��
	if (allAdjMatrix[departureCity][destinatedCity].size() > 0) {
		time.index = minTimeIndex;
		time.arriveTime = allAdjMatrix[departureCity][destinatedCity][minTimeIndex].arrivalTime;
	}

	return time;
}

vector<TrafficInfo> makeRouteTable(int strategyNum,int path[],MinTime time[],int departureCity, int destinatedCity)
{
	vector<TrafficInfo> tempRoute;
	unsigned int resultPath[CITYNUM];//����·��
	resultPath[CITYNUM - 1] = destinatedCity;//Ŀ�ĵ�
	int count = CITYNUM - 1;
	while (path[destinatedCity] != departureCity) {	//��û���ݵ����
		resultPath[--count] = path[destinatedCity];
		destinatedCity = path[destinatedCity];
	}
	resultPath[--count] = departureCity;//��ʼ��
	for (unsigned int i = count; i < CITYNUM - 1; i++) {
		unsigned int start = resultPath[i];//������ʼ��
		unsigned int end = resultPath[i + 1];//����Ŀ�ĵ�
		if (strategyNum == 0) {
			tempRoute.push_back(firstAdjMatrix[start][end]);//������뵽���vector
		}
		else if (strategyNum == 1) {
			tempRoute.push_back(allAdjMatrix[start][end][time[end].index]);//������뵽���vector
		}
	}
	return tempRoute;
}

int calculateTime(Result tempResult)
{
	int waitTime = 0;//��ĳ��վ�ȴ���ʱ��
	int moveTime = 0;//��ĳ��·�����ߵ�ʱ��
	for (unsigned int i = 0; i < tempResult.route.size(); i++) {
		if (i == 0) {	//��һ�˺���
			waitTime = tempResult.route[i].departureTime - tempResult.departureTime.time().hour();//��һ���������ʱ���ȥ���ﳵվʱ��
		}
		else {
			waitTime = tempResult.route[i].departureTime - tempResult.route[i - 1].arrivalTime;//�˺������ʱ���ȥ�ϴκ��ൽ��ʱ��
		}
		if (waitTime < 0) {	//��㵽����(��վ)���߿���
			waitTime = waitTime + 24;//�ٵ�һ����߿���
		}
		moveTime = tempResult.route[i].arrivalTime - tempResult.route[i].departureTime;//����ʱ���ȥ����ʱ��,���ƶ�ʱ��
		if (moveTime <= 0) {
			moveTime = moveTime + 24;//����
		}
		tempResult.sumTime += waitTime;//ʱ���ۼ�
		tempResult.sumTime += moveTime;//ʱ���ۼ�
	}
	return tempResult.sumTime;
}

void permutate(vector<vector<int>>& permResult, vector<int>& passCities, int begin)
{
	if (begin + 1 == passCities.size()) {	//�˴εݹ����
		permResult.push_back(passCities);
	}
	else {
		for (unsigned int i = begin; i < passCities.size(); i++) {
			swap(passCities[begin], passCities[i]);//����
			permutate(permResult, passCities, begin + 1);//�ݹ�
			swap(passCities[begin], passCities[i]);//�ݹ���ϻ���,������һ�ν���
		}
	}
}

void DFS(TrafficInfo preTraffic, int spendTime, vector<TrafficInfo>& tempResult, Result& finalResult,
	int destinatedCity,int limitTime,int depth,int& maxCost, vector<int>& passCities, int spendCost)
{
	if (spendTime > limitTime || depth > MAXDEPTH || spendCost >= maxCost) {	//����ʱ�����ƻ��߳����ݹ���Ȼ��߽�Ǯ����
		return;//������һ��
	}
	else if (preTraffic.destination == destinatedCity) {	//�����յ�
		//�˴��ж�tempResult�Ƿ�����ؾ���С��maxCost
		if (passCities.size() > 0) {	//ѡ���˱ؾ�����
			//���ж��Ƿ������������
			if (isHasPass(tempResult, passCities) == true) {
				maxCost = spendCost;
				finalResult.route = tempResult;
				finalResult.sumTime = spendTime;
				finalResult.sumCost = spendCost;//����final
			}
		}
		else {	//ûѡ�ؾ�����
			maxCost = spendCost;
			finalResult.route = tempResult;
			finalResult.sumTime = spendTime;
			finalResult.sumCost = spendCost;//����final
		}
		return;
	}
	else {	//����
		int departureCity = preTraffic.destination;//�˴εĳ�������,���ϴκ���ĵ������
		int departureTime = preTraffic.arrivalTime;//�˴γ�����ʱ��,���ϴκ���ĵ���ʱ��
		for (unsigned int i = 0; i < CITYNUM; i++) {
			if (i != departureCity) {
				for (unsigned j = 0; j < allAdjMatrix[departureCity][i].size(); j++) {
						//����spendTime
						///��spendCost
						int waitTime = allAdjMatrix[departureCity][i][j].departureTime - departureTime;
						if (waitTime < 0) {
							waitTime += 24;
						}
						int moveTime = allAdjMatrix[departureCity][i][j].arrivalTime
							- allAdjMatrix[departureCity][i][j].departureTime;
						if (moveTime < 0) {
							moveTime += 24;
						}
						spendTime += waitTime;
						spendTime += moveTime;
						//��spendCost
						spendCost += allAdjMatrix[departureCity][i][j].cost;
						//���˺���push_back��tempResult
						tempResult.push_back(allAdjMatrix[departureCity][i][j]);
						//����DFS
						DFS(allAdjMatrix[departureCity][i][j], spendTime, 
							tempResult, finalResult, destinatedCity, limitTime,depth++,maxCost,passCities,spendCost);
						tempResult.pop_back();//�Ժ��࿪ʼ��·�ߵݹ����,����pop_back��ȥ������һ�εݹ�
						depth--;//���غ� �ݹ���ȼ�һ
						spendTime -= waitTime;//����ʱ��ָ�
						spendTime -= moveTime;//����ʱ��ָ�
						spendCost -= allAdjMatrix[departureCity][i][j].cost;//���ѽ�Ǯ�ָ�
				}
			}
		}
	}
}

bool isHasPass(vector<TrafficInfo>& tempResult, vector<int>&passCities)
{

	unsigned int j = 0;
	for (unsigned int i = 0; i < passCities.size(); i++) {
		for (j = 0; j < tempResult.size(); j++) {
			if (passCities[i] == tempResult[j].destination) {
				break;
			}
		}
		if (j == tempResult.size()) {
			return false;
		}
	}
	return true;
}

PassengerState currentState(QDateTime pressTime)
{
	//���ȼ���pressTime �� result����� depaturetime
	int days = result.departureTime.daysTo(pressTime);//daysTo���� depatureTime��pressTime������,������������
	int hours = pressTime.time().hour() - result.departureTime.time().hour() + days * 24;//�������ʱ���ȥ�˶೤ʱ��
	int spendTime = 0;//ʵ�����е�ʱ��
	int waitTime = 0;//�ȴ���ʱ��
	int moveTime = 0;//��·�ϵ�ʱ��
	for (unsigned int i = 0; i < result.route.size(); i++) {
		if (i == 0) {
			waitTime = result.route[i].departureTime - result.departureTime.time().hour();//׼�������ȴ���һ�೵
		}
		else {
			waitTime = result.route[i].departureTime - result.route[i - 1].arrivalTime;//��ĳվ����һ�೵
		}
		if (waitTime < 0) {
			waitTime += 24;
		}
		spendTime += waitTime;
		if (spendTime > hours) {
			PassengerState state;
			state.isMoving = false;
			state.cityNumber = result.route[i].origin;
			return state;
		}
		moveTime = result.route[i].arrivalTime - result.route[i].departureTime;//��·�ϵ�ʱ��
		if (moveTime < 0) {
			moveTime += 24;
		}
		spendTime += moveTime;
		if (spendTime >= hours) {
			PassengerState state;
			state.isMoving = true;
			state.routeInfo = result.route[i];
			return state;
		}
	}
}