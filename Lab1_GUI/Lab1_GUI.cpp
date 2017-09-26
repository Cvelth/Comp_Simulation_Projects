#include "Lab1_GUI.hpp"
#include "Canvas.hpp"

Lab1_GUI::Lab1_GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.start, &QPushButton::clicked, this, &Lab1_GUI::start_simulation);
	connect(ui.time, &QSlider::valueChanged, this, &Lab1_GUI::change_time_coefficient);
	m_timer.setInterval(0);

	m_lifo_simulator.changeTimeCoefficient(1.f);
	m_lifo_simulator.initialize(cs::StorageType::LIFO);
	m_lifo_simulator.changeSigma(1.0);
	m_lifo_canvas = new Canvas(&m_lifo_simulator);
	ui.visualization_layout->addWidget(m_lifo_canvas);

	m_per_simulator.changeTimeCoefficient(1.f);
	m_per_simulator.initialize(cs::StorageType::PER);
	m_per_simulator.changeSigma(1.0);
	m_per_canvas = new Canvas(&m_per_simulator);
	ui.visualization_layout->addWidget(m_per_canvas);
}

Lab1_GUI::~Lab1_GUI() {
	delete m_lifo_canvas;
	delete m_per_canvas;
}

void Lab1_GUI::change_time_coefficient(int value) {
	m_lifo_simulator.changeTimeCoefficient(0.01f * value);
	m_per_simulator.changeTimeCoefficient(0.01f * value);
}

void Lab1_GUI::start_simulation() {
	m_lifo_simulator.changeLambda(ui.lambda->text().toFloat());
	m_lifo_simulator.changeMu(ui.mu->text().toFloat());
	m_lifo_simulator.changeTau(ui.tau->text().toFloat());
	m_per_simulator.changeLambda(ui.lambda->text().toFloat());
	m_per_simulator.changeMu(ui.mu->text().toFloat());
	m_per_simulator.changeTau(ui.tau->text().toFloat());

	if (!m_lifo_simulator.is_running())
		m_lifo_simulator.start();
	if (!m_per_simulator.is_running())
		m_per_simulator.start();

	ui.start->setText("Update");
	connect(&m_timer, &QTimer::timeout, m_lifo_canvas, &Canvas::redraw);
	connect(&m_timer, &QTimer::timeout, m_per_canvas, &Canvas::redraw);
	m_timer.start();
}