#include "SubWidget.hpp"
#include "ui_SubWidget.h"
#include <QAbstractButton>

SubWidget::SubWidget(QWidget *parent)
	: QWidget(parent) {

	ui = new Ui::SubWidget();
	ui->setupUi(this);

	connect(ui->enable, &QAbstractButton::clicked, this, &SubWidget::enable_event);
	enable_event();
}
SubWidget::~SubWidget() {
	delete ui;
}

bool SubWidget::areUniformsEnabled() {
	return ui->enable->isChecked();
}

float SubWidget::duration() {
	return ui->duration->text().toFloat();
}

float SubWidget::frequency() {
	return ui->frequency->text().toFloat();
}

void SubWidget::enable_event() {
	if (ui->enable->isChecked())
		ui->group->setEnabled(true);
	else
		ui->group->setEnabled(false);
}

void SubWidget::button_event() {
	if (isHidden())
		show();
	else
		hide();
}