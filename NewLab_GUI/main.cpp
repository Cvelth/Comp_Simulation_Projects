#include "NewLab_GUI.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NewLab_GUI w;
	w.show();
	return a.exec();
}
