#pragma once
#include <QtWidgets/QWidget>
#include "ui_NewLab_GUI.h"
#include <QTimer>
#include <vector>
#include <array>
#include <QtCharts>
namespace qs {
	class QueueingSystemSimulation;
}
class Canvas;
template <size_t Charts>
struct Simulator {
	qs::QueueingSystemSimulation *simulation;
	Canvas *canvas;
	std::array<QSplineSeries*, Charts> series;
	Simulator(qs::QueueingSystemSimulation *simulation, Canvas *canvas) : simulation(simulation), canvas(canvas) {
		for (size_t i = 0; i < Charts; i++)
			series[i] = new QSplineSeries();
	}
	Simulator(Simulator &&s) : simulation(s.simulation), canvas(s.canvas), series(s.series) {}
	virtual ~Simulator() {
		//for (size_t i = 0; i < Charts; i++)
		//	delete series[i];
	}
};

size_t const ChartNumber = 2;// 3;
class NewLab_GUI : public QWidget {
	Q_OBJECT
protected:
	size_t const m_statistics_step = 500;
	size_t m_step_counter = 0;
	QTimer m_redraw_timer, m_statistics_timer;
	std::vector<Simulator<ChartNumber>> simulators;
	std::array<QChart*, ChartNumber> charts;
	std::array<QValueAxis*, ChartNumber> axes;
	std::array<std::pair<double, double>, ChartNumber> extremums;
public:
	NewLab_GUI(QWidget *parent = Q_NULLPTR);
	~NewLab_GUI();
private:
	Ui::NewLab_GUIClass ui;
protected slots:
	void start();
	void change_time_coefficient(int value);
};