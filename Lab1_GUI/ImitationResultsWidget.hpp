#pragma once
#include <QWidget>
namespace Ui { class ImitationResultsWidget; };
class ImitationResultsWidget : public QWidget {
	Q_OBJECT

public:
	ImitationResultsWidget(QWidget *parent = Q_NULLPTR);
	ImitationResultsWidget(float lambda = 0.f, float mu = 0.f, float tau = 0.f,
		float x1 = 0.f, float x2 = 0.f, float x3 = 0.f, 
		float x4 = 0.f, float x5 = 0.f, float f = 0.f, 
		QWidget *parent = Q_NULLPTR);
	~ImitationResultsWidget();

	void initialize(float lambda = 0.f, float mu = 0.f, float tau = 0.f,
		float x1 = 0.f, float x2 = 0.f, float x3 = 0.f,
		float x4 = 0.f, float x5 = 0.f, float f = 0.f);

private:
	Ui::ImitationResultsWidget *ui;
};
