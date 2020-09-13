#pragma execution_character_set("utf-8")
#include "TipWindow.h"

TipWindow::TipWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(
		Qt::Window | Qt::WindowTitleHint
		| Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint
	);
	setFixedSize(130, 1);
	setWindowTitle("º∆À„÷–,«Î…‘∫Û......");
}