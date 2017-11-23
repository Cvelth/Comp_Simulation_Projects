#include "Properties.hpp"
#include "..\PetriNet\PetriNet.hpp"
NetDialog::NetDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
	ui.layout->addWidget(&w);
	connect(ui.ok, &QPushButton::clicked, [this]() {
		emit newNetCreated(w.network());
		close();
	});
	connect(ui.cancel, &QPushButton::clicked, [this]() {
		close();
	});
}
NetDialog::~NetDialog() {}
NetWidget::NetWidget(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
}
NetWidget::~NetWidget() {}
Canvas::NetType NetWidget::network() {
	return std::make_shared<pn::PetriNet<int>>(ui.name->text().toStdString(), float(ui.tau->value()), size_t(ui.cores->value()));
}