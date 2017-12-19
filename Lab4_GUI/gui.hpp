#pragma once
#include <QtWidgets/QWidget>
#include "ui_gui.h"
class Canvas;
class LinkWidget;
class gui : public QWidget {
	Q_OBJECT
public:
	gui(QWidget *parent = Q_NULLPTR);
	~gui();
protected:
	Ui::guiClass ui;
	Canvas *m_canvas;
	LinkWidget *m_link;
	protected slots:
	void deselect();
};