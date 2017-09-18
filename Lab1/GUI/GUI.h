#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUI.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::GUIClass ui;
};
