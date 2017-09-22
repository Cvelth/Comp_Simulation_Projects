#include "Canvas.hpp"
#include "..\ProcessorSimulator\Shared.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

void sendColor(cs::Color const& c) {
	glColor3f(c.r, c.g, c.b);
}

namespace default_colors {
	cs::Color lines = {0.7f, 0.3f, 0.9f};
	cs::Color elements = {0.95f, 0.75f, 0.95f};
}
using namespace default_colors;

void Canvas::initialDraw() {
	//Connection lines:
	glBegin(GL_LINES);
	sendColor(lines);
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
	sendColor(lines);
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
	sendColor(elements);
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
	sendColor(elements);
	for (float a = 0.0; a < 2 * M_PI; a += M_PI / 20)
		glVertex2f(sinf(a) / m_aspect_ratio * 0.25 + 0.5, cosf(a) * 0.25 + 0.5);
	glEnd();
}

void Canvas::drawGenerator() {}
