#include "Canvas.hpp"
Canvas::Canvas(QWidget *parent)	: QOpenGLWidget(parent) {
}
Canvas::~Canvas() {
}
void Canvas::initilizeNets() {
	for (auto it : m_nets) {

	}
}
void Canvas::draw(std::pair<NetType const, NetInfo>& net) {

}
void Canvas::initializeGL() {
	initializeOpenGLFunctions();
	initilizeNets();
}
void Canvas::resizeGL(int w, int h) {

}
void Canvas::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto it : m_nets)
		if (!std::get<0>(it.second)) {
			initilizeNets();
			break;
		}
	for (auto& it : m_nets)
		draw(it);
}