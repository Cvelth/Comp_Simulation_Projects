#pragma once
#include <QtWidgets/QWidget>
#include "ui_gui.h"
class Canvas;
class NetWidget;
class LinkWidget;
class gui : public QWidget {
	Q_OBJECT
public:
	gui(QWidget *parent = Q_NULLPTR);
	~gui();
private:
	Ui::guiClass ui;
	Canvas *m_canvas;
	NetWidget *m_net;
	LinkWidget *m_link;
protected slots:
	void deselect();
};