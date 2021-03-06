#include "Canvas.hpp"

Canvas::Canvas(qs::QueueingSystemSimulation *simulator, QWidget *parent)
	: QOpenGLWidget(parent), m_simulator(simulator), m_first(true) {
}

Canvas::~Canvas()
{
}

void Canvas::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0.10, 0.0, 0.15, 1.0);
	glLineWidth(3.0);
}

void Canvas::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-1.0, +1.0, -1.0, +1.0, -1.0, +1.0);
	m_aspect_ratio = float(w) / h;
}

void Canvas::paintGL() {
	initialDraw();
	drawGenerator();
	drawProcessor();
	drawStorage();
}

void Canvas::redraw() {
	update();
}