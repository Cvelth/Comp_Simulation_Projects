#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace cs {
	class ProcessorSimulator;
}

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
private:
	cs::ProcessorSimulator* m_simulator;
	float m_aspect_ratio;
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void initialDraw();

public:
	Canvas(cs::ProcessorSimulator* simulator, QWidget *parent = nullptr);
	~Canvas();

protected slots:
	void start_simulation();
};
