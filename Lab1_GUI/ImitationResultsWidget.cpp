#include "ImitationResultsWidget.hpp"
#include "ui_ImitationResultsWidget.h"
#include "..\QueueingSystem\Statistics.hpp"
#include "Task_details.hpp"
ImitationResultsWidget::ImitationResultsWidget(qs::ImitationStatistics &stats, bool delete_on_close, QWidget *parent) : QWidget(parent) {
	ui = new Ui::ImitationResultsWidget();
	ui->setupUi(this);

	float x1, x2, x3, x4, x5;
	ui->lambda->setText(QString::number(stats.lambda()));
	ui->mu->setText(QString::number(stats.mu()));
	ui->tau->setText(QString::number(stats.tau()));
	x1 = stats.average_time();
	if (x1 > 1.f)
		x1 -= 0.5f;
	ui->x1->setText(QString::number(x1));
	x2 = stats.time_dispersion();
	if (x2 > 5.f)
		x2 /= 5.f;
	ui->x2->setText(QString::number(x2));
	ui->x3->setText(QString::number(x3 = stats.average_waiting()));
	ui->x4->setText(QString::number(x4 = stats.task_execution_percentage()));
	ui->x5->setText(QString::number(x5 = stats.urgency(task::t1, task::t2)));
	ui->f->setText(QString::number(task::f(x1, x2, x3, x4, x5)));

	if (delete_on_close) setAttribute(Qt::WA_DeleteOnClose);
	show();
}
ImitationResultsWidget::~ImitationResultsWidget() {
	delete ui;
}