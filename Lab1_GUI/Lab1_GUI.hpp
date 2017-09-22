#pragma once
#include <QtWidgets/QWidget>
#include "..\ProcessorSimulator\ProcessorSimulator.hpp"
#include "ui_Lab1_GUI.h"

class Lab1_GUI : public QWidget
{
	Q_OBJECT

protected:
	cs::ProcessorSimulator m_simulator;

public:
	Lab1_GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::Lab1_GUIClass ui;
	
protected slots:
	void start_simulation();
};