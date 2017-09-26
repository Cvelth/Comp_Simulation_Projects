#pragma once
#include <QtWidgets/QWidget>
#include "..\ProcessorSimulator\ProcessorSimulator.hpp"
#include "ui_Lab1_GUI.h"
#include <QTimer>

class Canvas;

class Lab1_GUI : public QWidget
{
	Q_OBJECT

protected:
	QTimer m_timer;

	cs::ProcessorSimulator m_lifo_simulator;
	cs::ProcessorSimulator m_per_simulator;
	Canvas *m_lifo_canvas;
	Canvas *m_per_canvas;

public:
	Lab1_GUI(QWidget *parent = Q_NULLPTR);
	~Lab1_GUI();

private:
	Ui::Lab1_GUIClass ui;
	
protected slots:
	void start_simulation();
	void change_time_coefficient(int value);
};