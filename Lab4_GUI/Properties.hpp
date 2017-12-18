#pragma once
#include "..\DynamicProgramming\TravelingSalesmanProblem.hpp"
using namespace dp::TravelingSalesmanProblem;
#include <QDialog>
#include "ui_LinkWidget.h"
class LinkWidget : public QDialog {
	Q_OBJECT
public:
	LinkWidget(City first, City second, QWidget *parent = Q_NULLPTR);
	~LinkWidget();
	float to_second();
	float to_first();
private:
	Ui::LinkWidget ui;
signals:
	void updated(float, float);
public slots:
	void select(City first, City second, float to_second, float to_first);
};