#include "Canvas.hpp"
#include <QMatrix4x4>
#include <QMouseEvent>
Canvas::Canvas(QWidget *parent)	: QOpenGLWidget(parent) {

}
Canvas::~Canvas() {}
void Canvas::insertNet(NetType const net) {
	m_nets.insert(std::make_pair(net, std::make_tuple(0.f, 0.f)));
}
void Canvas::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0.2f, 0.f, 0.3f, 1.f);
	glLineWidth(1.5);
}
void Canvas::resizeGL(int w, int h) {
	m_width = w; m_height = h;
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, +1);
}
void Canvas::draw(std::pair<NetType const, NetInfo> &net) {
	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.7f, 1.f);
	float size = float(m_width) / 100.f;
	glVertex2f(std::get<0>(net.second) - size, std::get<1>(net.second));
	glVertex2f(std::get<0>(net.second), std::get<1>(net.second) - size);
	glVertex2f(std::get<0>(net.second) + size, std::get<1>(net.second));
	glVertex2f(std::get<0>(net.second), std::get<1>(net.second) + size);
	glEnd();
}
void Canvas::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& it : m_nets)
		draw(it);
}
#include <QMessageBox>
void Canvas::mousePressEvent(QMouseEvent *e) {
	float size = float(m_width) / 100.f;
	for (auto it : m_nets) 
		if (fabs(std::get<0>(it.second) - e->pos().x()) < size && fabs(std::get<1>(it.second) - e->pos().y()) < size) {
			QMessageBox::warning(this, tr("Placement Error"),
								 tr("You shouldn't create new device so close to existing one."));
			return;
		}
	m_nets.insert(std::make_pair(createNewNet(), std::make_tuple(float(e->pos().x()), float(e->pos().y()))));
	e->accept();
	update();
}
Canvas::NetType Canvas::createNewNet() {
	return std::make_shared<Net>(1.f);
}