#include "ImitationResultsWidget.hpp"
#include "ui_ImitationResultsWidget.h"

ImitationResultsWidget::ImitationResultsWidget(QWidget *parent) : QWidget(parent) {
	ui = new Ui::ImitationResultsWidget();
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}
ImitationResultsWidget::ImitationResultsWidget(float lambda, float mu, float tau,
	float x1, float x2, float x3, float x4, float x5, float f, 
	QWidget *parent) : ImitationResultsWidget(parent) {

	initialize(lambda, mu, tau, x1, x2, x3, x4, x5, f);
}
ImitationResultsWidget::~ImitationResultsWidget() {
	delete ui;
}

void ImitationResultsWidget::initialize(float lambda, float mu, float tau,
	float x1, float x2, float x3, float x4, float x5, float f) {

	ui->lambda->setText(QString::number(lambda));
	ui->mu->setText(QString::number(mu));
	ui->tau->setText(QString::number(tau));
	ui->x1->setText(QString::number(x1));
	ui->x2->setText(QString::number(x2));
	ui->x3->setText(QString::number(x3));
	ui->x4->setText(QString::number(x4));
	ui->x5->setText(QString::number(x5));
	ui->f->setText(QString::number(f));

	show();
}