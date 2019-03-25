#pragma once
#include <QtWidgets/QWidget>
#include "ui_NewLab_GUI.h"
class NewLab_GUI : public QWidget {
	Q_OBJECT
public:
	NewLab_GUI(QWidget *parent = Q_NULLPTR);
private:
	Ui::NewLab_GUIClass ui;
};