#include "Canvas.hpp"
#include <QMatrix4x4>
#include <QMouseEvent>
Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent), m_draw_line(false) {}
Canvas::~Canvas() {}
std::vector<Canvas::NetType> Canvas::nets() {
	std::vector<NetType> ret;
	for (auto& it : m_nets)
		ret.push_back(it.first);
	return ret;
}
std::vector<Canvas::NetType> const Canvas::nets() const {
	std::vector<NetType> ret;
	for (auto& it : m_nets)
		ret.push_back(it.first);
	return ret;
}
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
void Canvas::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	//Selection of a node
	glBegin(GL_QUADS);
	glColor3f(1.f, 0.2, 0.2f);
	if (m_selection == Selection::Net) draw(*m_selected_net, true);
	glEnd();

	//All the links
	for (auto& it : m_nets) 
		for (auto& it2 : it.first->transitions()) {
			glBegin(GL_LINE_LOOP);
			glColor3f(0.95f, 0.4f, 1.f);
			draw(it, *findNet(it2.first)); //HERE!!!!
			glEnd();
		}
	glBegin(GL_LINES);
	glColor3f(1.f, 0.2, 0.2f);
	if (m_selection == Selection::Link) draw(*m_selected_net, *m_selected_link);
	glEnd();

	//All the nodes
	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.5f, 0.9f);
	for (auto& it : m_nets) draw(it);
	glEnd();

	//Future link
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
	return false;
}
void Canvas::setLink(NetNode start, NetNode const end, float value) {
	start.first->link(end.first.get(), value);
}
void Canvas::clean() {
	m_nets.clear();
	m_selection = Selection::None;
	update();
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
	if (end) {
		m_selection = Selection::Net;
		m_selected_net = end;
		emit deselection_triggered();
		emit netSelected(end->first->name(), end->first->cores(), end->first->tau(), end->first->usage(), end->first->queue());
	} else {
		m_selection = Selection::None;
		emit deselection_triggered();
	}

	if (start && end && *start != *end) {
		if (!isLinked(*start, *end)) {
			LinkWidget d(start->first->name(), end->first->name(), this);
			connect(&d, &LinkWidget::updated, [this, start, end](float to_first, float to_second) {
				if (to_first)
					setLink(*start, *end, to_first);
				if (to_second)
					setLink(*end, *start, to_second);
			});
			d.exec();
		}
		m_selection = Selection::Link;
		m_selected_net = start;
		m_selected_link = end;
		emit deselection_triggered();
		emit linkSelected(start->first->name(), end->first->name(), start->first->weight(end->first.get()), end->first->weight(start->first.get()));
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
void Canvas::update_selected_node(std::string name, size_t cores, float tau) {
	if (m_selection == Selection::Net) {
		m_selected_net->first->update(name, cores, tau);
	} else {
		QMessageBox::warning(this, tr("Selection Error"),
							 tr("A net must be selected for it to be updated."));
		return;
	}
}
void Canvas::update_selected_link(float to_second, float to_first) {
	if (m_selection == Selection::Link) {
		m_selected_net->first->update_link(m_selected_link->first.get(), to_second);
		m_selected_link->first->update_link(m_selected_net->first.get(), to_first);
	} else {
		QMessageBox::warning(this, tr("Selection Error"),
							 tr("A link must be selected for it to be updated."));
		return;
	}
}
#include "..\ArcMath\ArcMath.hpp"
void Canvas::draw(NetNode &from, NetNode &to) {
	auto points = arc_math::generate(std::get<0>(from.second), std::get<1>(from.second), 
									 std::get<0>(to.second), std::get<1>(to.second));
	for (size_t i = 0; i < points.size() - 1; i += 2)
		glVertex2f(points[i], points[i + 1]);
}