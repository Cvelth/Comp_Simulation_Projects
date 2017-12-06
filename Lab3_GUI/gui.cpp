#include "gui.hpp"
#include <QPushButton>
#include "..\PetriNet\PetriNetTheoreticalCalculation.hpp"
#include "..\Lab2_GUI\Canvas.hpp"
#include "Results.hpp"
gui_l3::gui_l3(QWidget *parent) : gui(parent) {
	ui.buttons->addWidget(m_b = new QPushButton("Theoretical Calculation"));
	connect(m_b, &QPushButton::clicked, [this]() {
		std::vector<size_t> tasks;
		for (size_t i = 0u; i <= ui.tasks->value(); i++) tasks.push_back(i);
		auto w = new Results(pn::PetriNetTheoreticalCalculation<size_t>::calculate(m_canvas->nets(), tasks));
		w->setAttribute(Qt::WA_DeleteOnClose);
		w->show();
	});
}
gui_l3::~gui_l3() {
	delete m_b;
	delete m_canvas;
	delete m_net;
	delete m_link;
	exit(0);
}