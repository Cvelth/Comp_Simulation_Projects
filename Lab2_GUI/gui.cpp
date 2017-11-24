#include "gui.hpp"
#include "Canvas.hpp"
#include "Properties.hpp"
gui::~gui() {
	delete m_canvas;
	delete m_net;
	delete m_link;
}
void gui::deselect() {
	m_net->hide();
	m_link->hide();
}
#include "..\PetriNet\PetriNetSystemSimulator.hpp"
gui::gui(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.canvasLayout->addWidget(m_canvas = new Canvas());
	ui.propertiesLayout->addWidget(m_net = new NetWidget());
	ui.propertiesLayout->addWidget(m_link = new LinkWidget("", ""));

	connect(m_canvas, &Canvas::netSelected, m_net, &NetWidget::select);
	connect(m_canvas, &Canvas::linkSelected, m_link, &LinkWidget::select);
	connect(m_canvas, &Canvas::deselection_triggered, this, &gui::deselect);
	connect(m_net, &NetWidget::updated, m_canvas, &Canvas::update_selected_node);
	connect(m_link, &LinkWidget::updated, m_canvas, &Canvas::update_selected_link);
	m_net->hide();
	m_link->hide();

	connect(ui.start, &QPushButton::clicked, [this]() {
		std::vector<size_t> tasks;
		for (size_t i = 0u; i < ui.tasks->value(); i++) tasks.push_back(i);
		pn::PetriNetSystemSimulator<size_t>::simulate(m_canvas->nets(), tasks, ui.total_tasks->value());
	});
	connect(ui.clean, &QPushButton::clicked, [this]() {
		m_canvas->clean();
	});
}