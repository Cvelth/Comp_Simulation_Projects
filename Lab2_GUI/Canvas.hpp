#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <unordered_map>
#include <memory>
#include "..\PetriNet\PetriNet.hpp"
using Net = pn::PetriNet<int>;
class QMatrix4x4;
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:
	using NetType = std::shared_ptr<Net>;
	using NetInfo = std::tuple<float, float>;
	using NetNode = std::pair<NetType const, NetInfo>;
	enum class Selection {
		None, Net, Link
	};
private:
	std::unordered_map<NetType, NetInfo> m_nets;
protected:
	size_t m_height;
	size_t m_width;
	size_t m_last_mouse_x;
	size_t m_last_mouse_y;
	size_t m_current_mouse_x;
	size_t m_current_mouse_y;
	bool m_draw_line;
	Selection m_selection;
	NetNode* m_selected_net;
	NetNode* m_selected_link;
protected:
	virtual void draw(NetNode &net, bool selected = false);
	virtual void draw(NetNode &from, NetNode &to);
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
	virtual void mousePressEvent(QMouseEvent *e) override;
	virtual void mouseReleaseEvent(QMouseEvent *e) override;
	virtual void mouseMoveEvent(QMouseEvent *e) override;
	virtual void createNewNet(float x = 0.f, float y = 0.f);
	virtual NetNode* findNet(size_t x, size_t y);
	virtual NetNode* findNet(Net *net);
	virtual bool isLinked(NetNode const start, NetNode const end) const;
	virtual void setLink(NetNode start, NetNode const end, float value);
public:
	Canvas(QWidget *parent = Q_NULLPTR);
	~Canvas();
signals:
	void netSelected(std::string name, size_t cores, float tau, float usage);
	void linkSelected(std::string first_name, std::string second_name, float to_second, float to_first);
	void deselection_triggered();
public slots:
	void insertNet(NetType const net, float x = 0.f, float y = 0.f);
};