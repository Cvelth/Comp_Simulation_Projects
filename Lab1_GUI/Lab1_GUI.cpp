#include "Lab1_GUI.hpp"
#include "Canvas.hpp"

Lab1_GUI::Lab1_GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.start, &QPushButton::clicked, this, &Lab1_GUI::start_simulation);
	connect(ui.time, &QSlider::valueChanged, this, &Lab1_GUI::change_time_coefficient);
	m_timer.setInterval(16);

	m_simulator.changeTimeCoefficient(1.f);
	m_simulator.initialize(cs::StorageType::LIFO);
	m_simulator.changeSigma(1.0);
	m_canvas = new Canvas(&m_simulator);
	ui.visualization_layout->addWidget(m_canvas);
}

Lab1_GUI::~Lab1_GUI() {
	delete m_canvas;
}

void Lab1_GUI::change_time_coefficient(int value) {
	m_simulator.changeTimeCoefficient(0.01f * value);
}

void Lab1_GUI::start_simulation() {
	m_simulator.stop();
	m_simulator.changeLambda(ui.lambda->text().toFloat());
	m_simulator.changeMu(ui.mu->text().toFloat());
	m_simulator.changeTau(ui.tau->text().toFloat());
	m_simulator.start();
	ui.start->setText("Restart");
	connect(&m_timer, &QTimer::timeout, m_canvas, &Canvas::redraw);
	m_timer.start();
}