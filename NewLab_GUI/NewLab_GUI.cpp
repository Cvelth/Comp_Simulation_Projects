#include "NewLab_GUI.hpp"
#include "..\QueueingSystem\QueueingSystem.hpp"
#include "Canvas.hpp"

template <typename C>
void add(C &c, qs::SystemType type, float time_coefficient = 1.f) {
	auto temp = new qs::QueueingSystemSimulation();
	c.emplace_back(std::pair(temp, new Canvas(temp)));
	c.back().first->initialize(type, time_coefficient);
}

NewLab_GUI::NewLab_GUI(QWidget *parent)	: QWidget(parent) {
	ui.setupUi(this);
	connect(ui.start, &QPushButton::clicked, this, &NewLab_GUI::start);
	connect(ui.time, &QSlider::valueChanged, this, &NewLab_GUI::change_time_coefficient);
	m_timer.setInterval(0);

	add(simulators, qs::SystemType::LIFO);
	add(simulators, qs::SystemType::PER);
	add(simulators, qs::SystemType::EDF);

	for (auto s : simulators)
		ui.visualization_layout->addWidget(s.second);
}

NewLab_GUI::~NewLab_GUI() {
	for (auto s : simulators) {
		delete s.second;
		delete s.first;
	}
}

void NewLab_GUI::change_time_coefficient(int value) {
	for (auto &s : simulators)
		s.first->changeTimeCoefficient(1e-3f * value);
}

void NewLab_GUI::start() {
	for (auto s : simulators) {
		s.first->changeLambda(ui.lambda->value());
		s.first->changeSigma(ui.sigma->value());
		s.first->changeMu(ui.mu->value());
		s.first->changeTau(ui.tau->value());
		s.first->changeExpiration(ui.exp->value());

		if (!s.first->is_running())
			s.first->start();

		connect(&m_timer, &QTimer::timeout, s.second, &Canvas::redraw);
	}
	ui.start->setText("Update");
	m_timer.start();
}