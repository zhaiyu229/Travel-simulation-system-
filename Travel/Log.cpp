#include "Log.h"

fstream logFile;

bool openFile()
{
	logFile.open("log.txt", ios::out | ios::app);//׷��дģʽ
	if (logFile.is_open() == false) {
		return false;
	}
	else {
		return true;
	}
}

void updateFile(string content)
{
	logFile << content << endl;//д���ļ�
}