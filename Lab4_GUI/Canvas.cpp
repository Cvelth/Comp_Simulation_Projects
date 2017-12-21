#include "Canvas.hpp"
#include <QMatrix4x4>
#include <QMouseEvent>
void Canvas::draw(Position &city) {
	float size = float(m_width) / 100.f;

	glVertex2f(city.first - size, city.second);
	glVertex2f(city.first, city.second - size);
	glVertex2f(city.first + size, city.second);
	glVertex2f(city.first, city.second + size);
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
void Canvas::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	//All the links
	for (City i = 0; i < m_cities.size(); i++)
		for (City j = 0; j < m_cities.size(); j++)
			if (m_links[i][j] != 0.f) {
				glBegin(GL_LINE_STRIP);
				glColor3f(0.95f, 0.4f, 1.f);
				draw(i, j);
				glEnd();
			}
	glBegin(GL_LINES);
	glColor3f(1.f, 0.2, 0.2f);
	if (m_selection) draw(m_selected_from, m_selected_to);
	glEnd();

	//Answer links
	if (m_draw_answer) {
		for (size_t i = 0; i < m_answer.size() - 1; i++) {
			glBegin(GL_LINE_STRIP);
			glColor3f(0.95f, 0.4f, 0.f);
			draw(m_answer[i], m_answer[i + 1]);
			glEnd();
		}

		glBegin(GL_LINE_STRIP);
		glColor3f(0.95f, 0.4f, 0.f);
		draw(m_answer[m_answer.size() - 1], m_answer[0]);
		glEnd();
	}

	//All the cities
	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.5f, 0.9f);
	for (auto it : m_cities) draw(it);
	glEnd();

	//Future link
	if (m_draw_line) {
		glBegin(GL_LINE_STRIP);
		glColor3f(0.8f, 0.3f, 0.5f);
		draw(m_last_mouse_x, m_last_mouse_y, m_current_mouse_x, m_current_mouse_y);
		glEnd();
	}
}
void Canvas::mousePressEvent(QMouseEvent *e) {
	m_last_mouse_x = e->pos().x();
	m_last_mouse_y = e->pos().y();
	m_draw_line = true;
}
void Canvas::mouseMoveEvent(QMouseEvent *e) {
	m_current_mouse_x = e->pos().x();
	m_current_mouse_y = e->pos().y();
	update();
}
City Canvas::find_city(float x, float y) {
	for (size_t i = 0; i < m_cities.size(); i++)
		if (fabs(m_cities[i].first - x) <= 8.f && fabs(m_cities[i].second - y) <= 8.f)
			return i;
	return -1;
}
City Canvas::find_city(Position &position) {
	return find_city(position.first, position.second);
}
Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent), m_draw_line(false), m_selection(false), m_draw_answer(false) {}
Canvas::~Canvas() {}
void Canvas::clean() {
	m_cities.clear();
	m_links.clear();
	m_selection = false;
	update();
}
void Canvas::answer(std::vector<dp::TravelingSalesmanProblem::City> answer) {
	m_draw_answer = true;
	m_answer = answer;
	update();
}
void Canvas::addCity(Position &position) {
	m_cities.push_back(position);
	m_links.resize(m_links.size() + 1);
	for (auto &link : m_links)
		link.resize(m_links.size());
}
void Canvas::addCity(float x, float y) {
	return addCity(Position(x, y));
}
#include "Properties.hpp"
void Canvas::mouseReleaseEvent(QMouseEvent *e) {
	m_selection = false;
	emit deselection_triggered();

	auto start = find_city(m_last_mouse_x, m_last_mouse_y);
	auto end = find_city(e->pos().x(), e->pos().y());
	if (start != -1 && end != -1 && start != end) {
		if (m_links[start][end] == 0.f) {
			LinkWidget d(start, end, this);
			connect(&d, &LinkWidget::updated, [this, start, end](float to_second, float to_first) {
				m_links[start][end] = to_second;
				m_links[end][start] = to_first;
			});
			d.exec();
		}
		m_selection = true;
		m_selected_from = start;
		m_selected_to = end;
		emit deselection_triggered();
		emit linkSelected(start, end, m_links[start][end], m_links[end][start]);
	}
	m_draw_line = false;
	update();
}
#include <QMessageBox>
void Canvas::mouseDoubleClickEvent(QMouseEvent *e) {
	float size = float(m_width) / 100.f;
	for (auto it : m_cities)
		if (fabs(it.first - e->pos().x()) < size && fabs(it.second - e->pos().y()) < size) {
			QMessageBox::warning(this, tr("Placement Error"),
								 tr("You shouldn't create new city so close to existing one."));
			return;
		}
	addCity(e->pos().x(), e->pos().y());
	e->accept();
	update();
}
void Canvas::update_selected_link(float to_second, float to_first) {
	if (m_selection) {
		m_links[m_selected_from][m_selected_to] = to_second;
		m_links[m_selected_to][m_selected_from] = to_first;
	} else {
		QMessageBox::warning(this, tr("Selection Error"),
							 tr("A link must be selected for it to be updated."));
		return;
	}
}
#include "..\ArcMath\ArcMath.hpp"
void Canvas::draw(float sx, float sy, float ex, float ey) {
	auto points = arc_math::generate(sx, sy, ex, ey, 1.5f);
	for (int i = 0; i < int(points.size()) - 1; i += 2)
		glVertex2f(points[i], points[i + 1]);
}
void Canvas::draw(City &from, City &to) {
	return draw(m_cities[from].first, m_cities[from].second,
				m_cities[to].first, m_cities[to].second);
}