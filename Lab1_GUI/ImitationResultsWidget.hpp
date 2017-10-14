#pragma once

#include <QWidget>
namespace Ui { class ImitationResultsWidget; };

class ImitationResultsWidget : public QWidget {
	Q_OBJECT

public:
	ImitationResultsWidget(QWidget *parent = Q_NULLPTR);
	~ImitationResultsWidget();

private:
	Ui::ImitationResultsWidget *ui;
};
