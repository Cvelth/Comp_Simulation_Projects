#include "Lab1_GUI.hpp"
#include "Canvas.hpp"
#include "Task_details.hpp"

Lab1_GUI::Lab1_GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.simulate, &QPushButton::clicked, this, &Lab1_GUI::start_simulation);
	connect(ui.imitate, &QPushButton::clicked, this, &Lab1_GUI::start_imitation);
	connect(ui.time, &QSlider::valueChanged, this, &Lab1_GUI::change_time_coefficient);
	m_timer.setInterval(0);

	m_lifo_simulator.changeTimeCoefficient(1.f);
	m_per_simulator.changeTimeCoefficient(1.f);
	m_lifo_simulator.initialize(qs::SystemType::LIFO);
	m_per_simulator.initialize(qs::SystemType::PER);
	m_lifo_simulator.changeSigma(task::sigma);
	m_per_simulator.changeSigma(task::sigma);
	m_lifo_canvas = new Canvas(&m_lifo_simulator);
	m_per_canvas = new Canvas(&m_per_simulator);
	ui.visualization_layout->addWidget(m_lifo_canvas);
	ui.visualization_layout->addWidget(m_per_canvas);

	m_lifo_imitator.initialize(qs::SystemType::LIFO);
	m_per_imitator.initialize(qs::SystemType::PER);
	m_lifo_imitator.changeSigma(1.0);
	m_per_imitator.changeSigma(1.0);
}

Lab1_GUI::~Lab1_GUI() {
	delete m_lifo_canvas;
	delete m_per_canvas;
}

void Lab1_GUI::change_time_coefficient(int value) {
	m_lifo_simulator.changeTimeCoefficient(1e-3f * value);
	m_per_simulator.changeTimeCoefficient(1e-3f * value);
}

void Lab1_GUI::start_simulation() {
	m_lifo_simulator.changeLambda(ui.lambda->text().toFloat());
	m_per_simulator.changeLambda(ui.lambda->text().toFloat());
	m_lifo_simulator.changeMu(ui.mu->text().toFloat());
	m_per_simulator.changeMu(ui.mu->text().toFloat());
	m_lifo_simulator.changeTau(ui.tau->text().toFloat());
	m_per_simulator.changeTau(ui.tau->text().toFloat());

	if (!m_lifo_simulator.is_running())
		m_lifo_simulator.start();
	if (!m_per_simulator.is_running())
		m_per_simulator.start();

	ui.simulate->setText("Update");
	connect(&m_timer, &QTimer::timeout, m_lifo_canvas, &Canvas::redraw);
	connect(&m_timer, &QTimer::timeout, m_per_canvas, &Canvas::redraw);
	m_timer.start();
}

#include "ImitationResultsWidget.hpp"
#include "..\QueueingSystem\Statistics.hpp"
void Lab1_GUI::start_imitation() {
	m_lifo_imitator.changeLambda(ui.lambda->text().toFloat());
	m_per_imitator.changeLambda(ui.lambda->text().toFloat());
	m_lifo_imitator.changeMu(ui.mu->text().toFloat());
	m_per_imitator.changeMu(ui.mu->text().toFloat());
	m_lifo_imitator.changeTau(ui.tau->text().toFloat());
	m_per_imitator.changeTau(ui.tau->text().toFloat());
	
	size_t number = ui.n->text().toUInt();

	qs::ImitationStatistics lifo_stats(ui.lambda->text().toFloat(), ui.mu->text().toFloat(), ui.tau->text().toFloat());
	qs::ImitationStatistics per_stats(ui.lambda->text().toFloat(), ui.mu->text().toFloat(), ui.tau->text().toFloat());

	if (!m_lifo_imitator.is_running())
		m_lifo_imitator.run(number, &lifo_stats, false);	
	if (!m_per_imitator.is_running())
		m_per_imitator.run(number, &per_stats, false);
	
	QWidget *w = new QWidget();
	w->setAttribute(Qt::WA_DeleteOnClose);
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(new ImitationResultsWidget(lifo_stats, true));
	layout->addWidget(new ImitationResultsWidget(per_stats, true));
	w->setLayout(layout);
	w->show();
}