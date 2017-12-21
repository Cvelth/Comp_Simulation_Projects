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
#include <QTableWidget>
#include <random>
MatrixWidget::MatrixWidget(std::vector<std::vector<Distance>> links) {
	ui.setupUi(this);
	m_links = links;
	fill();
	connect(ui.matrix, &QTableWidget::cellChanged, [this](int i, int j) {
		if (i != j) m_links[i][j] = ui.matrix->item(i, j)->text().toDouble();
	});
	connect(ui.randomize, &QPushButton::clicked, [this]() {
		std::mt19937_64 g;
		std::uniform_real_distribution<float> d(0.f, 100.f);
		for (size_t i = 0; i < m_links.size(); i++)
			for (size_t j = 0; j < m_links.size(); j++)
				if (i != j) 
					m_links[i][j] = d(g);
		fill();
	});
}
MatrixWidget::~MatrixWidget() {}
void MatrixWidget::fill() {
	auto size = m_links.size();
	ui.matrix->setColumnCount(size);
	ui.matrix->setRowCount(size);
	for (size_t i = 0; i < size; i++) {
		ui.matrix->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
		ui.matrix->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
		for (size_t j = 0; j < size; j++)
			ui.matrix->setItem(i, j, new QTableWidgetItem(QString::number(m_links[i][j])));
	}
}
#include <QMessageBox>
MatrixDialog::MatrixDialog(std::vector<std::vector<Distance>> links) {
	ui.setupUi(this);
	connect(ui.ok, &QPushButton::clicked, [this]() {
		emit confirm(m_widget->result());
		close();
	});
	connect(ui.cancel, &QPushButton::clicked, [this]() {
		close();
	});
	ui.layout->addWidget(m_widget = new MatrixWidget(links));
}
MatrixDialog::~MatrixDialog() {}