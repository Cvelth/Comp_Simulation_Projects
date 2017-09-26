#include "Canvas.hpp"
#include "..\ProcessorSimulator\Shared.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "..\ProcessorSimulator\ProcessorSimulator.hpp"
#include "..\ProcessorSimulator\TaskGenerator.hpp"
#include "..\ProcessorSimulator\TaskProcessor.hpp"
#include "..\ProcessorSimulator\TaskStorage.hpp"

void sendColor(cs::Color const& c) {
	glColor3f(c.r, c.g, c.b);
}

namespace default_colors {
	cs::Color lines = {0.7f, 0.3f, 0.9f};
	cs::Color elements = {0.95f, 0.75f, 0.95f};
	cs::Color background = {0.1f, 0.f, 0.15f};
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
	glVertex2f(-0.05, -0.2);
	glVertex2f(-0.05, -0.2);
	glVertex2f(-0.15, -0.2);
	//stack -> center
	glVertex2f(+0.05, +0.5);
	glVertex2f(+0.05, -0.6);
	glVertex2f(+0.15, -0.6);
	glVertex2f(-0.15, -0.6);
	//center -> edge
	glVertex2f(+1.0, +0.5);
	glVertex2f(+0.05, +0.5);

	//processor -> repush_stack
	if (m_simulator->type() == cs::StorageType::PER) {
		glVertex2f(+0.86, +0.5);
		glVertex2f(+0.86, -0.3);
	}

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
	glVertex2f(+0.95, +0.50);
	glVertex2f(+0.92, +0.53);
	glVertex2f(+0.92, +0.47);

	//to repush_stack
	if (m_simulator->type() == cs::StorageType::PER) {
		glVertex2f(+0.86, +0.20);
		glVertex2f(+0.89, +0.24);
		glVertex2f(+0.83, +0.24);
	}

	glEnd();
}

void Canvas::drawGenerator() {
	float percent = m_simulator->generator()->getCurrentPercent() / 1.e+3f;
	percent = percent > 1.f ? 1.f : percent;
	float point = 0.6f * percent - 0.8f;

	glBegin(GL_QUADS);
	sendColor(m_simulator->generator()->getCurrentColor());
	glVertex2f(-0.8, +0.55);
	glVertex2f(-0.8, +0.45);
	glVertex2f(point, +0.45);
	glVertex2f(point, +0.55);

	sendColor(elements);
	glVertex2f(point, +0.55);
	glVertex2f(point, +0.45);
	glVertex2f(-0.2, +0.45);
	glVertex2f(-0.2, +0.55);
	glEnd();
}

void Canvas::drawProcessor() {
	float percent = m_simulator->processor()->getCurrentPercent() / 1.e+3f;
	percent = percent > 1.f ? 1.f : percent;
	float angle = M_PI * 2.f * percent;
	const float points = 60;
	
	glBegin(GL_POLYGON);
	sendColor(elements);
	glVertex2f(0.5f, 0.5f);
	for (float a = angle; a <= M_PI * 2.f + M_PI / points; a += M_PI / points)
		glVertex2f(sinf(a) / m_aspect_ratio * 0.25 + 0.5, cosf(a) * 0.25 + 0.5);
	glVertex2f(0.5f, 0.5f);
	glEnd();

	glBegin(GL_POLYGON);
	sendColor(m_simulator->processor()->getCurrentColor());
	glVertex2f(0.5f, 0.5f);
	for (float a = 0.f; a <= angle + M_PI / points; a += M_PI / points)
		glVertex2f(sinf(a) / m_aspect_ratio * 0.25 + 0.5, cosf(a) * 0.25 + 0.5);
	glVertex2f(0.5f, 0.5f);
	glEnd();

	glBegin(GL_POLYGON);
	sendColor(background);
	for (float a = 0.0; a < M_PI * 2.f; a += M_PI / points)
		glVertex2f(sinf(a) / m_aspect_ratio * 0.15 + 0.5, cosf(a) * 0.15 + 0.5);
	glEnd();
}

void Canvas::drawStorage() {
	if (m_simulator->type() == cs::StorageType::LIFO) {
		float y = 0.f;
		glBegin(GL_QUADS);
		m_simulator->storage()->for_each_push([&y, this](cs::Task const& task) {
			sendColor(task.color());
			glVertex2f(-0.4, y);
			glVertex2f(+0.4, y);
			y -= 0.04;
			glVertex2f(+0.4, y);
			glVertex2f(-0.4, y);
		});
		sendColor(elements);
		if (y > -1.0) {
			glVertex2f(-0.4, y);
			glVertex2f(+0.4, y);
			glVertex2f(+0.4, -1.0);
			glVertex2f(-0.4, -1.0);
		}
		glEnd();
	} else if (m_simulator->type() == cs::StorageType::PER) {
		float y = 0.f;
		glBegin(GL_QUADS);
		m_simulator->storage()->for_each_push([&y, this](cs::Task const& task) {
			sendColor(task.color());
			glVertex2f(-0.9, y);
			glVertex2f(-0.1, y);
			y -= 0.04;
			glVertex2f(-0.1, y);
			glVertex2f(-0.9, y);
		});
		sendColor(elements);
		if (y > -1.0) {
			glVertex2f(-0.9, y);
			glVertex2f(-0.1, y);
			glVertex2f(-0.1, -1.0);
			glVertex2f(-0.9, -1.0);
		}

		y = 0.f;
		m_simulator->storage()->for_each_repush([&y, this](cs::Task const& task) {
			sendColor(task.color());
			glVertex2f(+0.9, y);
			glVertex2f(+0.1, y);
			y -= 0.04; 
			glVertex2f(+0.1, y);
			glVertex2f(+0.9, y);
		});
		sendColor(elements);
		if (y > -0.8) {
			glVertex2f(+0.9, y);
			glVertex2f(+0.1, y);
			glVertex2f(+0.1, -1.0);
			glVertex2f(+0.9, -1.0);
		}
		glEnd();
	}
}