#include "Properties.hpp"
NetDialog::NetDialog(QWidget *parent)
	: QDialog(parent) {
	ui.setupUi(this);
}
NetDialog::~NetDialog() {}

NetWidget::NetWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
}
NetWidget::~NetWidget() {}