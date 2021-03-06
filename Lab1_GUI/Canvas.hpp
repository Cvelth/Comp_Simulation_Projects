#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace qs {
	class QueueingSystemSimulation;
}

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
private:
	qs::QueueingSystemSimulation* m_simulator;
	float m_aspect_ratio;
	bool m_first;
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void initialDraw();
	virtual void drawGenerator();
	virtual void drawProcessor();
	virtual void drawStorage();
public:
	Canvas(qs::QueueingSystemSimulation *simulator, QWidget *parent = nullptr);
	~Canvas();

public slots:
	void redraw();
};
