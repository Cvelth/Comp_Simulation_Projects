#include "Results.hpp"
#include <QLabel>
#include <QLineEdit>
Result::Result(std::pair<std::string, float> value) {
	m_label = new QLabel(QString("The usage for ") + QString::fromStdString(value.first) + " is");
	m_label->setAlignment(Qt::AlignRight);
	addWidget(m_label);

	m_value = new QLineEdit(QString::number(value.second));
	m_value->setReadOnly(true);
	addWidget(m_value);
}
Result::~Result() {
	delete m_value;
	delete m_label;
}

Results::Results(std::vector<std::pair<std::string, float>> values, QWidget *parent) : QWidget(parent) {
	setFont(QFont("Verdana", 14));
	m_layout = new QVBoxLayout();
	for (auto it : values) {
		m_results.push_back(new Result(it));
		m_layout->addLayout(m_results.back());
	}
	setLayout(m_layout);
}
Results::~Results() {
	for (auto it : m_results)
		delete it;
}