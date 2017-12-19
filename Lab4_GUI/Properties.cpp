#include "Properties.hpp"
LinkWidget::LinkWidget(City first, City second, QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
	ui.to_second_label->setText(QString::number(first) + " -> " + QString::number(second));
	ui.to_first_label->setText(QString::number(second) + " -> " + QString::number(first));
	connect(ui.save, &QPushButton::clicked, [this]() { 
		emit updated(to_second(), to_first());
		close();
	});
}
LinkWidget::~LinkWidget() {}
float LinkWidget::to_second() { return ui.to_second->value(); }
float LinkWidget::to_first() { return ui.to_first->value(); }
void LinkWidget::select(City first, City second, float to_second, float to_first) {
	ui.to_second_label->setText(QString::number(first) + " -> " + QString::number(second));
	ui.to_first_label->setText(QString::number(second) + " -> " + QString::number(first));
	ui.to_second->setValue(to_second);
	ui.to_first->setValue(to_first);
	show();
}