#include "TravelWindow.h"
#include "Solution.h"
#include "Log.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	readFromFile();//���ļ����ȡ��Ϣ
	makeMatrix();//�����ڽӾ���
	if (openFile() == false) {
		exit(0);
	}
	QApplication a(argc, argv);
	TravelWindow w;
	w.show();
	return a.exec();
}
