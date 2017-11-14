#include "gui.hpp"
#include "Canvas.hpp"
gui::gui(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	ui.canvasLayout->addWidget(m_canvas = new Canvas());
}
gui::~gui() {
	delete m_canvas;
}