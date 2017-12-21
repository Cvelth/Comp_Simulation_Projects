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

	ui.splitter->setStretchFactor(0, 9);
	ui.splitter->setStretchFactor(1, 1);

	connect(ui.find, &QPushButton::clicked, [this]() {
		m_canvas->answer(dp::TravelingSalesmanProblem::solve(m_canvas->links()));
	});
	connect(ui.matrix, &QPushButton::clicked, [this]() {
		MatrixDialog d(m_canvas->links());
		connect(&d, &MatrixDialog::confirm, [this](std::vector<std::vector<Distance>> links) {
			m_canvas->links(links);
		});
		d.exec();
	});
}