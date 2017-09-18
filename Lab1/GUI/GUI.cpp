#include "GUI.h"
#include "..\Simulation\ProcessorSimulator.hpp"

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	cs::ProcessorSimulator p;
	p.initialize(cs::StorageType::LIFO);
	p.changeLambda(2.3);
	p.start();
}
