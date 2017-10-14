#include "ImitationResultsWidget.hpp"
#include "ui_ImitationResultsWidget.h"

ImitationResultsWidget::ImitationResultsWidget(QWidget *parent)
	: QWidget(parent) {
	ui = new Ui::ImitationResultsWidget();
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

ImitationResultsWidget::~ImitationResultsWidget() {
	delete ui;
}
