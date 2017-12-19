#include "gui.hpp"
#include "Canvas.hpp"
#include "Properties.hpp"
gui::~gui() {
	delete m_canvas;
	delete m_link;
}
void gui::deselect() {
	m_link->hide();
}
#include "..\DynamicProgramming\TravelingSalesmanProblem.hpp"
gui::gui(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.canvasLayout->addWidget(m_canvas = new Canvas());
	ui.propertiesLayout->addWidget(m_link = new LinkWidget(0, 0));

	connect(m_canvas, &Canvas::linkSelected, m_link, &LinkWidget::select);
	connect(m_canvas, &Canvas::deselection_triggered, this, &gui::deselect);
	connect(m_link, &LinkWidget::updated, m_canvas, &Canvas::update_selected_link);
	m_link->hide();

	ui.splitter->setStretchFactor(0, 8);
	ui.splitter->setStretchFactor(1, 2);

	connect(ui.find, &QPushButton::clicked, [this]() {
		//Find the answer.
	});
	connect(ui.clean, &QPushButton::clicked, [this]() {
		m_canvas->clean();
	});
}