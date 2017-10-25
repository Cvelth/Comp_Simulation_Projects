#pragma once

#include <QWidget>
namespace Ui { class SubWidget; };

class SubWidget : public QWidget
{
	Q_OBJECT

public:
	SubWidget(QWidget *parent = Q_NULLPTR);
	~SubWidget();

	bool areUniformsEnabled();
	float duration();
	float frequency();

private:
	Ui::SubWidget *ui;

public slots:
	void button_event();
	void enable_event();
};
