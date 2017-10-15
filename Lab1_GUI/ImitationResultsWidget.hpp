#pragma once
#include <QWidget>
namespace Ui { class ImitationResultsWidget; };
namespace qs {
	class ImitationStatistics;
}
class ImitationResultsWidget : public QWidget {	
	Q_OBJECT
public:
	ImitationResultsWidget(qs::ImitationStatistics &stats, bool delete_on_close = false, QWidget *parent = Q_NULLPTR);
	~ImitationResultsWidget();
private:
	Ui::ImitationResultsWidget *ui;
};
