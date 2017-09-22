#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
private:
	float m_aspect_ratio;
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void initialDraw();

public:
	Canvas(QWidget *parent = nullptr);
	~Canvas();
};
