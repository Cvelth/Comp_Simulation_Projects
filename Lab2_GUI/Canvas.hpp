#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <unordered_map>
#include <memory>
namespace pn {
	class PetriNet;
}
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
private:
	using NetType = std::shared_ptr<pn::PetriNet>;
	using NetInfo = std::tuple<bool, size_t, size_t>;
	std::unordered_map<NetType, NetInfo> m_nets;
protected:
	virtual void initilizeNets();
	virtual void draw(std::pair<NetType const, NetInfo> &net);
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
public:
	Canvas(QWidget *parent = Q_NULLPTR);
	~Canvas();
};