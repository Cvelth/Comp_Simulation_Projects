#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <unordered_map>
#include <memory>
#include "..\PetriNet\PetriNet.hpp"
using Net = pn::PetriNet<int>;
class QMatrix4x4;
enum class ShaderType {
	Vertex, Fragment
};
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
private:
	using NetType = std::shared_ptr<Net>;
	using NetInfo = std::tuple<float, float>;
	std::unordered_map<NetType, NetInfo> m_nets;
protected:
	size_t m_height;
	size_t m_width;
protected:
	virtual void draw(std::pair<NetType const, NetInfo> &net);
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void mousePressEvent(QMouseEvent *e) override;
	virtual NetType createNewNet();
public:
	Canvas(QWidget *parent = Q_NULLPTR);
	~Canvas();

	virtual void insertNet(NetType const net);
};