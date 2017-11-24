#include "Properties.hpp"
Usage::Usage(QString name, QString value, QWidget *parent) {
	ui.setupUi(this);
	ui.label->setText(name);
	ui.value->setText(value);
	ui.value->setReadOnly(true);
}
Usage::~Usage() {}
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
NetWidget::NetWidget(QWidget *parent) : QWidget(parent), m_update(nullptr) {
	ui.setupUi(this);
}
NetWidget::~NetWidget() {
	for (auto it : m_usage)
		delete it;
	if (m_update)
		delete m_update;
}
Canvas::NetType NetWidget::network() {
	return std::make_shared<Net>(ui.name->text().toStdString(), float(ui.tau->value()), size_t(ui.cores->value()));
}
void NetWidget::select(std::string name, size_t cores, float tau, std::vector<float> usage) {
	ui.name->setText(QString::fromStdString(name));
	ui.cores->setValue(cores);
	ui.tau->setValue(tau);

	for (auto it : m_usage)
		delete it;
	m_usage.clear();
	if (cores == 1) {
		m_usage.push_back(new Usage("Usage", QString::number(usage[0] * 100) + "%"));
		ui.usage->addWidget(m_usage.front());
	} else
		for (size_t i = 0; i < usage.size(); i++) {
			m_usage.push_back(new Usage("Usage of core #" + QString::number(i), QString::number(usage[i] * 100) + "%"));
			ui.usage->addWidget(m_usage[i]);
		}
	if (m_update)
		delete m_update;
	m_update = new QPushButton("Update");
	connect(m_update, &QPushButton::clicked, [this]() {
		emit updated(ui.name->text().toStdString(), ui.cores->value(), ui.tau->value());
	});
	ui.usage->addWidget(m_update);
	show();
}
LinkWidget::LinkWidget(std::string first, std::string second, QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
	ui.first->setText(QString::fromStdString(first));
	ui.second->setText(QString::fromStdString(second));
	connect(ui.save, &QPushButton::clicked, [this]() { 
		emit updated(to_second(), to_first());
		close();
	});
}
LinkWidget::~LinkWidget() {}
float LinkWidget::to_second() { return ui.to_second->value(); }
float LinkWidget::to_first() { return ui.to_first->value(); }
void LinkWidget::select(std::string first_name, std::string second_name, float to_second, float to_first) {
	ui.first->setText(QString::fromStdString(first_name));
	ui.second->setText(QString::fromStdString(second_name));
	ui.to_second->setValue(to_second);
	ui.to_first->setValue(to_first);
	show();
}