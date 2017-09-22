#include "Lab1_GUI.hpp"
#include "Canvas.hpp"

Lab1_GUI::Lab1_GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.start, &QPushButton::clicked, this, &Lab1_GUI::start_simulation);

	m_simulator.changeTimeCoefficient(1.e-1f);
	m_simulator.initialize(cs::StorageType::LIFO);
	m_simulator.changeSigma(1.0);
	ui.visualization_layout->addWidget(new Canvas(&m_simulator));
}

void Lab1_GUI::start_simulation() {
	m_simulator.stop();
	m_simulator.changeLambda(ui.lambda->text().toFloat());
	m_simulator.changeMu(ui.mu->text().toFloat());
	m_simulator.changeTau(ui.tau->text().toFloat());
	m_simulator.start();
	ui.start->setText("Restart");
}