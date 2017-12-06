#pragma once
#include <QVBoxLayout>
class QLabel;
class QLineEdit;
class Result : public QVBoxLayout {
	//Q_OBJECT
protected:
	QLabel *m_label;
	QLineEdit *m_value;
public:
	explicit Result(std::pair<std::string, float> value);
	virtual ~Result();
};
#include <QWidget>
class Results : public QWidget {
	//Q_OBJECT
protected:
	QVBoxLayout *m_layout;
	std::vector<Result*> m_results;
public:
	explicit Results(std::vector<std::pair<std::string, float>> values, QWidget *parent = Q_NULLPTR);
	virtual ~Results();
};