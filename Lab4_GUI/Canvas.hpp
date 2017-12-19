#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "..\DynamicProgramming\TravelingSalesmanProblem.hpp"
using namespace dp::TravelingSalesmanProblem;
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:
	using Position = std::pair<float, float>;
private:
	std::vector<Position> m_cities;
	std::vector<std::vector<Distance>> m_links;
protected:
	size_t m_height;
	size_t m_width;
	size_t m_last_mouse_x;
	size_t m_last_mouse_y;
	size_t m_current_mouse_x;
	size_t m_current_mouse_y;
	bool m_draw_line;
	bool m_selection;
	City m_selected_from;
	City m_selected_to;
protected:
	virtual void draw(Position &city);
	virtual void draw(City &from, City &to);
	virtual void draw(float sx, float sy, float ex, float ey);
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
	virtual void mousePressEvent(QMouseEvent *e) override;
	virtual void mouseMoveEvent(QMouseEvent *e) override;
	virtual void mouseReleaseEvent(QMouseEvent *e) override;

	virtual City find_city(float x, float y);
	virtual City find_city(Position &position);
public:
	Canvas(QWidget *parent = Q_NULLPTR);
	~Canvas();
	void clean();
signals:
	void linkSelected(City first, City second, float to_second, float to_first);
	void deselection_triggered();
public slots:
	void addCity(Position &position);
	void addCity(float x, float y);
	void update_selected_link(float to_second, float to_first);
};