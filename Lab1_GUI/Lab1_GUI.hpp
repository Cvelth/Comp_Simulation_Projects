#pragma once

#include <QtWidgets/QWidget>
#include "ui_Lab1_GUI.h"

class Lab1_GUI : public QWidget
{
	Q_OBJECT

public:
	Lab1_GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::Lab1_GUIClass ui;
};