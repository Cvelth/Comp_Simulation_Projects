#include "gui.hpp"
#include "Canvas.hpp"
#include "Properties.hpp"
gui::gui(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.canvasLayout->addWidget(m_canvas = new Canvas());
	ui.propertiesLayout->addWidget(m_net = new NetWidget());
	ui.propertiesLayout->addWidget(m_link = new LinkWidget("", ""));

	connect(m_canvas, &Canvas::netSelected, m_net, &NetWidget::select);
	connect(m_canvas, &Canvas::linkSelected, m_link, &LinkWidget::select);
	connect(m_canvas, &Canvas::deselection_triggered, this, &gui::deselect);
	m_net->hide();
	m_link->hide();
}
gui::~gui() {
	delete m_canvas;
	delete m_net;
	delete m_link;
}
void gui::deselect() {
	m_net->hide();
	m_link->hide();
}