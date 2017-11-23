#pragma once
#include <QWidget>
#include "ui_NetWidget.h"
class NetWidget : public QWidget {
	Q_OBJECT
public:
	NetWidget(QWidget *parent = Q_NULLPTR);
	~NetWidget();
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
};