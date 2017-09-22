#include "Lab1_GUI.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Lab1_GUI w;
	w.show();
	return a.exec();
}
