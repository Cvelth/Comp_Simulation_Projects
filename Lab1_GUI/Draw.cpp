#include "Canvas.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

void Canvas::initialDraw() {
	//Connection lines:
	glBegin(GL_LINES);
	glColor3f(0.7, 0.3, 0.9);
	//edge -> generator
	glVertex2f(-1.0, +0.5);
	glVertex2f(-0.8, +0.5);
	//generator -> center
	glVertex2f(-0.2, +0.5);
	glVertex2f(-0.05, +0.5);
	//center -> stack
	glVertex2f(-0.05, +0.5);
	glVertex2f(-0.05, +0.0);
	//stack -> center
	glVertex2f(+0.05, +0.5);
	glVertex2f(+0.05, +0.0);
	//center -> edge
	glVertex2f(+1.0, +0.5);
	glVertex2f(+0.05, +0.5);
	glEnd();

	//Arrows:
	glBegin(GL_TRIANGLES);
	glColor3f(0.7, 0.3, 0.9);
	//to generator
	glVertex2f(-0.85, +0.50);
	glVertex2f(-0.88, +0.53);
	glVertex2f(-0.88, +0.47);
	//to stack
	glVertex2f(-0.05, +0.20);
	glVertex2f(-0.08, +0.24);
	glVertex2f(-0.02, +0.24);
	//from stack
	glVertex2f(+0.05, +0.24);
	glVertex2f(+0.08, +0.20);
	glVertex2f(+0.02, +0.20);
	//from processor
	glVertex2f(+0.85, +0.50);
	glVertex2f(+0.83, +0.53);
	glVertex2f(+0.83, +0.47);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.95, 0.75, 0.95);
	//Generator
	glVertex2f(-0.8, +0.6);
	glVertex2f(-0.8, +0.4);
	glVertex2f(-0.2, +0.4);
	glVertex2f(-0.2, +0.6);
	//Stack
	glVertex2f(-0.4, -0.0);
	glVertex2f(+0.4, -0.0);
	glVertex2f(+0.4, -0.8);
	glVertex2f(-0.4, -0.8);
	glEnd();

	//Processor
	glBegin(GL_POLYGON);
	glColor3f(0.95, 0.75, 0.95);
	for (float a = 0.0; a < 2 * M_PI; a += M_PI / 20)
		glVertex2f(sinf(a) / m_aspect_ratio * 0.25 + 0.5, cosf(a) * 0.25 + 0.5);
	glEnd();
}
