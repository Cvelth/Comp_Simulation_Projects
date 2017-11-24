#pragma once
#include <QWidget>
#include "ui_Usage.h"
class Usage : public QWidget {
	Q_OBJECT
public:
	Usage(QString name = "", QString value = "", QWidget *parent = Q_NULLPTR);
	~Usage();
private:
	Ui::Usage ui;
};
#include "Canvas.hpp"
#include "ui_NetWidget.h"
class NetWidget : public QWidget {
	Q_OBJECT
public:
	NetWidget(QWidget *parent = Q_NULLPTR);
	~NetWidget();
	Canvas::NetType network();
private:
	Ui::NetWidget ui;
	std::vector<Usage*> m_usage;
public slots:
	void select(std::string name, size_t cores, float tau, std::vector<float> usage);
};
#include <QDialog>
#include "ui_LinkWidget.h"
class LinkWidget : public QDialog {
	Q_OBJECT
public:
	LinkWidget(std::string from, std::string to, QWidget *parent = Q_NULLPTR);
	~LinkWidget();
	float to_second();
	float to_first();
private:
	Ui::LinkWidget ui;
signals:
	void value_updated(float, float);
public slots:
	void select(std::string first_name, std::string second_name, float to_second, float to_first);
};
#include "ui_WidgetDialog.h"
class NetDialog : public QDialog {
	Q_OBJECT
public:
	NetDialog(QWidget *parent = Q_NULLPTR);
	~NetDialog();
private:
	Ui::WidgetDialog ui;
	NetWidget w;
signals:
	void newNetCreated(Canvas::NetType);
};