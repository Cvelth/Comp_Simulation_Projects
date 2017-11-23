#pragma once
#include <QWidget>
#include "ui_NetWidget.h"
#include "Canvas.hpp"
class NetWidget : public QWidget {
	Q_OBJECT
public:
	NetWidget(QWidget *parent = Q_NULLPTR);
	~NetWidget();
	Canvas::NetType network();
private:
	Ui::NetWidget ui;
};
#include <QDialog>
#include "ui_NetDialog.h"
class NetDialog : public QDialog {
	Q_OBJECT
public:
	NetDialog(QWidget *parent = Q_NULLPTR);
	~NetDialog();
private:
	Ui::NetDialog ui;
	NetWidget w;
signals:
	void newNetCreated(Canvas::NetType);
};