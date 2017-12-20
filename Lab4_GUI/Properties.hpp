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
#include <QWidget>
#include "ui_MatrixWidget.h"
#include <vector>
class MatrixWidget : public QWidget {
	Q_OBJECT
public:
	MatrixWidget(std::vector<std::vector<Distance>> links);
	~MatrixWidget();
	std::vector<std::vector<Distance>> result() { return m_links; }
protected:
	std::vector<std::vector<Distance>> m_links;
private:
	Ui::MatrixWidget ui;
};
#include "ui_WidgetDialog.h"
class MatrixDialog : public QDialog {
	Q_OBJECT
public:
	MatrixDialog(std::vector<std::vector<Distance>> links);
	~MatrixDialog();
private:
	MatrixWidget *m_widget;
	Ui::WidgetDialog ui;
signals:
	void confirm(std::vector<std::vector<Distance>>);
};