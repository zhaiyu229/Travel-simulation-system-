#pragma once
#include <fstream>
#include <string>
using namespace std;

extern fstream logFile;

bool openFile();//����־�ļ�
void updateFile(string content);
/*
	����:������־�ļ�
	content ��Ҫ׷�ӵ�����
*/