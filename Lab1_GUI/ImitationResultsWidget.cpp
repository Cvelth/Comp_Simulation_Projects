#include "ImitationResultsWidget.hpp"
#include "ui_ImitationResultsWidget.h"
#include "..\QueueingSystem\Statistics.hpp"
ImitationResultsWidget::ImitationResultsWidget(qs::ImitationStatistics const& stats, bool delete_on_close, QWidget *parent) : QWidget(parent) {
	ui = new Ui::ImitationResultsWidget();
	ui->setupUi(this);

	ui->lambda->setText(QString::number(stats.lambda()));
	ui->mu->setText(QString::number(stats.mu()));
	ui->tau->setText(QString::number(stats.tau()));
	//ui->x1->setText(QString::number(x1));
	//ui->x2->setText(QString::number(x2));
	//ui->x3->setText(QString::number(x3));
	//ui->x4->setText(QString::number(x4));
	//ui->x5->setText(QString::number(x5));
	//ui->f->setText(QString::number(f));

	if (delete_on_close) setAttribute(Qt::WA_DeleteOnClose);
	show();
}
ImitationResultsWidget::~ImitationResultsWidget() {
	delete ui;
}