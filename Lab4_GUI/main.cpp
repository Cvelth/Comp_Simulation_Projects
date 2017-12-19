#include "gui.hpp"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	gui w;
	w.showMaximized();
	return a.exec();
}