#include "gui.hpp"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	gui_l3 w;
	w.show();
	return a.exec();
}