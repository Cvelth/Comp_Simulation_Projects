#include "Lab1_GUI.hpp"
#include "..\ProcessorSimulator\ProcessorSimulator.hpp"
#include "Canvas.hpp"

Lab1_GUI::Lab1_GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.visualization_layout->addWidget(new Canvas());

	cs::ProcessorSimulator p;
	p.changeTimeCoefficient(1.e-6f);
	p.initialize(cs::StorageType::LIFO);
	p.changeLambda(2.3);
	p.changeMu(5.2);
	p.changeSigma(1.0);
	p.changeTau(1.0);
	p.start();
}
