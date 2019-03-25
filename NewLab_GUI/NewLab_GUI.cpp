#include "NewLab_GUI.hpp"
#include "..\QueueingSystem\QueueingSystem.hpp"
#include "Canvas.hpp"

template <typename C>
void add(C &c, qs::SystemType type, float time_coefficient = 1.f) {
	auto temp = new qs::QueueingSystemSimulation();
	c.push_back(Simulator<ChartNumber>(temp, new Canvas(temp)));
	c.back().simulation->initialize(type, time_coefficient);
}

NewLab_GUI::NewLab_GUI(QWidget *parent)	: QWidget(parent) {
	ui.setupUi(this);
	connect(ui.start, &QPushButton::clicked, this, &NewLab_GUI::start);
	connect(ui.time, &QSlider::valueChanged, this, &NewLab_GUI::change_time_coefficient);
	m_redraw_timer.setInterval(0);
	m_statistics_timer.setInterval(m_statistics_step);

	add(simulators, qs::SystemType::LIFO);
	add(simulators, qs::SystemType::PER);
	add(simulators, qs::SystemType::EDF);

	for (auto &chart : charts) {
		chart = new QChart();
		chart->legend()->hide();
		//chart->setAnimationOptions(QChart::AllAnimations);
		QChartView *view = new QChartView(chart);
		view->setRenderHint(QPainter::Antialiasing);
		ui.chart_layout->addWidget(view);
	}
	for (auto &axis : axes) {
		axis = new QValueAxis();
		axis->setTickCount(1);
		axis->setRange(0, m_statistics_step);
	}

	for (auto &s : simulators) {
		s.simulation->synchronize(*simulators.front().simulation);
		ui.visualization_layout->addWidget(s.canvas);
		for (size_t i = 0; i < s.series.size(); i++) {
			s.series[i]->append(0, 0);
			charts[i]->addSeries(s.series[i]);
		}
	}
	for (size_t i = 0; i < charts.size(); i++) {
		charts[i]->createDefaultAxes();
		for (auto &s : simulators)
			charts[i]->setAxisX(axes[i], s.series[i]);
		extremums[i] = std::pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
	}
}

NewLab_GUI::~NewLab_GUI() {
	for (auto &s : simulators) {
		delete s.simulation;
		delete s.canvas;
	}
}

void NewLab_GUI::change_time_coefficient(int value) {
	for (auto &s : simulators)
		s.simulation->changeTimeCoefficient(1e-3f * value);
}

#include <QGraphicsItem>
void NewLab_GUI::start() {
	for (auto &s : simulators) {
		s.simulation->changeLambda(ui.lambda->value());
		s.simulation->changeSigma(ui.sigma->value());
		s.simulation->changeMu(ui.mu->value());
		s.simulation->changeTau(ui.tau->value());
		s.simulation->changeExpiration(ui.exp->value());

		if (!s.simulation->is_running())
			s.simulation->start();

		connect(&m_redraw_timer, &QTimer::timeout, s.canvas, &Canvas::redraw);
	}
	for (auto &chart : charts) {
		connect(&m_statistics_timer, &QTimer::timeout, this, [this, &chart]() {
			m_step_counter++;
			for (auto &s : simulators) {
				auto processor = s.simulation->processor();
				s.series[0]->append(m_step_counter * m_statistics_step, processor->completed());
				s.series[1]->append(m_step_counter * m_statistics_step, processor->dropped());
				//s.series[2]->append(m_step_counter * m_statistics_step, processor->queue_size());
			}
			for (size_t i = 0; i < charts.size(); i++) {
				//axes[i]->setTickCount(m_step_counter);
				axes[i]->setRange(0, m_step_counter * m_statistics_step);
			}
			//chart->update(); 
		});
	}
	for (auto &s : simulators)
		for (size_t i = 0; i < charts.size(); i++)
			connect(s.series[i], &QSplineSeries::pointAdded, [&s, i, this](int index) {
				auto y = s.series[i]->at(index).y();
				if (y < extremums[i].first || y > extremums[i].second) {
					if (y < extremums[i].first)
						extremums[i].first = y;
					if (y > extremums[i].second)
						extremums[i].second = y;
					charts[i]->axisY()->setRange(extremums[i].first, extremums[i].second);
				}
			});
	ui.start->setText("Update");
	m_redraw_timer.start();
	m_statistics_timer.start();
}