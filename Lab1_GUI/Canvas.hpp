#pragma once

#include <QOpenGLWidget>

class Canvas : public QOpenGLWidget
{
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

public:
	Canvas(QWidget *parent);
	~Canvas();
};
