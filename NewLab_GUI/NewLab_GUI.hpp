#pragma once
#include <QtWidgets/QWidget>
#include "ui_NewLab_GUI.h"
#include <QTimer>
#include <vector>
namespace qs {
	class QueueingSystemSimulation;
}
class Canvas;
class NewLab_GUI : public QWidget {
	Q_OBJECT
protected:
	QTimer m_timer;
	std::vector<std::pair<qs::QueueingSystemSimulation*, Canvas*>> simulators;
public:
	NewLab_GUI(QWidget *parent = Q_NULLPTR);
	~NewLab_GUI();
private:
	Ui::NewLab_GUIClass ui;
protected slots:
	void start();
	void change_time_coefficient(int value);
};