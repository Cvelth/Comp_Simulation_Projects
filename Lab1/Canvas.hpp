#pragma once
#include <QOpenGLWidget.h>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

public:
	Canvas(QWidget *parent);
	~Canvas();
};
