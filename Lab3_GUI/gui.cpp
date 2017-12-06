#include "gui.hpp"
#include <QPushButton>
#include <sstream>
#include "..\PetriNet\PetriNetSystemSimulator.hpp"
#include "..\PetriNet\PetriNetTheoreticalCalculation.hpp"
#include "..\Lab2_GUI\Canvas.hpp"
#include "Results.hpp"
gui_l3::gui_l3(QWidget *parent) : gui(parent) {
	ui.buttons->addWidget(m_b = new QPushButton("Theoretical Calculation"));
	connect(m_b, &QPushButton::clicked, [this]() {
		std::vector<size_t> tasks;
		for (size_t i = 0u; i <= ui.tasks->value(); i++) tasks.push_back(i);
		pn::PetriNetSystemSimulator<size_t>::simulate(m_canvas->nets(), tasks, ui.total_tasks->value() * m_canvas->nets().size() * m_canvas->nets().size());
		std::vector<std::pair<std::string, float>> results;
		for (auto it : m_canvas->nets()) {
			auto temp = it->usage();
			if (temp.size() == 1)
				results.push_back(std::make_pair(it->name(), temp[0]));
			else
				for (size_t i = 0; i < temp.size(); i++) {
					std::stringstream s;
					s << it->name() << "[" << i << "]";
					results.push_back(std::make_pair(s.str(), temp[i]));
				}
		}
		
		auto w = new Results(results);
		//auto w = new Results(pn::PetriNetTheoreticalCalculation<size_t>::calculate(m_canvas->nets(), tasks));
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