#pragma once
#include <QWidget>
namespace Ui { class SubWidget; };

class SubWidget : public QWidget {
	Ui::SubWidget *ui;
public:
	SubWidget(QWidget *parent = Q_NULLPTR);
	~SubWidget();

	bool areUniformsEnabled();
	float duration();
	float frequency();=

public slots:
	void button_event();
	void enable_event();
};