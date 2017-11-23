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
LinkWidget::LinkWidget(std::string first, std::string second, QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
	ui.first->setText(QString::fromStdString(first));
	ui.second->setText(QString::fromStdString(second));
	connect(ui.save, &QPushButton::clicked, [this]() { 
		emit value_updated(to_second(), to_first());
		close();
	});
}
LinkWidget::~LinkWidget() {}
float LinkWidget::to_second() { return ui.to_second->value(); }
float LinkWidget::to_first() { return ui.to_first->value(); }