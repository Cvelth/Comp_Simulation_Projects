#pragma once
#include <QtWidgets/QWidget>
#include "..\QueueingSystem\QueueingSystem.hpp"
#include "ui_Lab1_GUI.h"
#include <QTimer>

class Canvas;
class SubWidget;

class Lab1_GUI : public QWidget
{
	Q_OBJECT

protected:
	QTimer m_timer;

	qs::QueueingSystemSimulation m_lifo_simulator;
	qs::QueueingSystemSimulation m_per_simulator;
	qs::QueueingSystemImitation m_lifo_imitator;
	qs::QueueingSystemImitation m_per_imitator;
	Canvas *m_lifo_canvas;
	Canvas *m_per_canvas;

	SubWidget *m_sw;

public:
	Lab1_GUI(QWidget *parent = Q_NULLPTR);
	~Lab1_GUI();

private:
	Ui::Lab1_GUIClass ui;
	
protected slots:
	void start_simulation();
	void start_imitation();
	void change_time_coefficient(int value);
};