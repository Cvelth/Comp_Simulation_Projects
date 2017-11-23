#include "Canvas.hpp"
#include <QMatrix4x4>
#include <QMouseEvent>
Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent), m_draw_line(false) {}
Canvas::~Canvas() {}
void Canvas::insertNet(NetType const net, float x, float y) {
	m_nets.insert(std::make_pair(net, std::make_tuple(x, y)));
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
void Canvas::draw(NetNode &net, bool selected) {
	float size = float(m_width) / 100.f;
	if (selected)
		size *= 1.7f;
	glVertex2f(std::get<0>(net.second) - size, std::get<1>(net.second));
	glVertex2f(std::get<0>(net.second), std::get<1>(net.second) - size);
	glVertex2f(std::get<0>(net.second) + size, std::get<1>(net.second));
	glVertex2f(std::get<0>(net.second), std::get<1>(net.second) + size);
}
void Canvas::draw(NetNode &from, NetNode &to) {
	glVertex2f(std::get<0>(from.second), std::get<1>(from.second));
	glVertex2f(std::get<0>(to.second), std::get<1>(to.second));
}
void Canvas::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glColor3f(0.95f, 0.4f, 1.f);
	for (auto& it : m_nets) 
		for (auto& it2 : it.first->transitions()) {
			draw(it, *findNet(it2.first));
		}
	glColor3f(1.f, 0.2, 0.2f);
	if (m_selection == Selection::Link) draw(*m_selected_net, *m_selected_link);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.f, 0.2, 0.2f);
	if (m_selection == Selection::Net) draw(*m_selected_net, true);
	glColor3f(0.9f, 0.5f, 0.9f);
	for (auto& it : m_nets) draw(it);
	glEnd();

	if (m_draw_line) {
		glBegin(GL_LINES);
		glColor3f(0.8f, 0.3f, 0.5f);
		glVertex2f(m_last_mouse_x, m_last_mouse_y);
		glVertex2f(m_current_mouse_x, m_current_mouse_y);
		glEnd();
	}
}
void Canvas::mouseMoveEvent(QMouseEvent *e) {
	m_current_mouse_x = e->pos().x();
	m_current_mouse_y = e->pos().y();
	update();
}
void Canvas::mousePressEvent(QMouseEvent *e) {
	auto n = findNet(e->pos().x(), e->pos().y());
	if (n) {
		m_selection = Selection::Net;
		m_selected_net = n;
	} else
		m_selection = Selection::None;
	m_last_mouse_x = e->pos().x();
	m_last_mouse_y = e->pos().y();
	m_draw_line = true;
}
Canvas::NetNode* Canvas::findNet(size_t x, size_t y) {
	for (auto& it : m_nets)
		if (fabs(std::get<0>(it.second) - x) <= 8.f && fabs(std::get<1>(it.second) - y) <= 8.f)
			return &it;
	return nullptr;
}
Canvas::NetNode* Canvas::findNet(Net *net) {
	for (auto& it : m_nets)
		if (*it.first == *net)
			return &it;
	return nullptr;
}
bool Canvas::isLinked(NetNode const start, NetNode const end) const {
	for (auto it : start.first->transitions())
		if (*end.first == *it.first)
			return true;
	for (auto it : end.first->transitions())
		if (*start.first == *it.first)
			return true;
	return false;
}
void Canvas::setLink(NetNode start, NetNode const end, float value) {
	start.first->link(end.first.get(), value);
}
#include "Properties.hpp"
void Canvas::createNewNet(float x, float y) {
	NetDialog d(this);
	connect(&d, &NetDialog::newNetCreated, [this, x, y](NetType const net) {
		insertNet(net, x, y);
	});
	d.exec();
}
void Canvas::mouseReleaseEvent(QMouseEvent *e) {
	auto start = findNet(m_last_mouse_x, m_last_mouse_y);
	auto end = findNet(e->pos().x(), e->pos().y());
	if (start && end && *start != *end) {
		if (isLinked(*start, *end)) {
			m_selection = Selection::Link;
			m_selected_net = start;
			m_selected_link = end;
		} else {
			LinkWidget d(start->first->name(), end->first->name(), this);
			connect(&d, &LinkWidget::value_updated, [this, start, end](float value) {
				setLink(*start, *end, value);
			});
			if (d.exec() == QDialog::Accepted) {
				m_selection = Selection::Link;
				m_selected_net = start;
				m_selected_link = end;
			}
		}
	}
	m_draw_line = false;
	update();
}
#include <QMessageBox>
void Canvas::mouseDoubleClickEvent(QMouseEvent *e) {
	float size = float(m_width) / 100.f;
	for (auto it : m_nets) 
		if (fabs(std::get<0>(it.second) - e->pos().x()) < size && fabs(std::get<1>(it.second) - e->pos().y()) < size) {
			QMessageBox::warning(this, tr("Placement Error"),
								 tr("You shouldn't create new device so close to existing one."));
			return;
		}
	createNewNet(e->pos().x(), e->pos().y());
	e->accept();
	update();
}