#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <qopenglfunctions_3_3_core.h>
#include <unordered_map>
#include <memory>
#include "..\PetriNet\PetriNet.hpp"
using Net = pn::PetriNet<int>;
class QMatrix4x4;
enum class ShaderType;
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
	Q_OBJECT
private:
	using NetType = std::shared_ptr<Net>;
	using NetInfo = std::tuple<bool, GLuint, size_t, size_t>;
	std::unordered_map<NetType, NetInfo> m_nets;
private:
	GLuint m_vertexArray;
	GLuint m_program;
	QMatrix4x4 *m_projection;
protected:
	virtual void initializeNets();
	virtual void draw(std::pair<NetType const, NetInfo> &net);
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
protected:
	GLuint compileSource(ShaderType type, const char * sourceText);
	GLuint link(const std::initializer_list<GLuint>& shaders);
public:
	Canvas(QWidget *parent = Q_NULLPTR);
	~Canvas();

	virtual void insertNet(NetType const net);
};