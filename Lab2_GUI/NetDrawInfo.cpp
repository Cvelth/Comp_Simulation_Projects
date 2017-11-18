#include "Canvas.hpp"
#define _USE_MATH_DEFINES
#include "Math.h"
constexpr size_t Coords = 2;
constexpr size_t Circles = 3;
constexpr size_t Circle_Size = 24;
constexpr size_t Squares = 2;
constexpr size_t Square_Size = 4;
constexpr size_t Straight_Arrows = 5;
constexpr size_t Straight_Arrow_Size = 6;
constexpr size_t Array_Size = Circles * Coords * Circle_Size 
							+ Squares * Coords * Square_Size 
							+ Straight_Arrows * Coords * Straight_Arrow_Size;
float res[Array_Size];
void Canvas::initializeNets() {
	for (auto& it : m_nets)
		if (!std::get<0>(it.second)) {
			glGenBuffers(1, &std::get<1>(it.second));
			glBindBuffer(GL_ARRAY_BUFFER, std::get<1>(it.second));
			size_t i = 0;
			//Circles
			for (float f = 0.f; f <= M_PI * 2.1f; f += M_PI / Circle_Size * 2.1f) {
				res[i++] = 0.2f * cosf(f) - 0.7f;
				res[i++] = 0.2f * sinf(f);
			}
			for (float f = 0.f; f <= M_PI * 2.1f; f += M_PI / Circle_Size * 2.1f) {
				res[i++] = 0.2f * cosf(f) + 0.1f;
				res[i++] = 0.2f * sinf(f);
			}
			for (float f = 0.f; f <= M_PI * 2.1f; f += M_PI / Circle_Size * 2.1f) {
				res[i++] = 0.2f * cosf(f) + 0.1f;
				res[i++] = 0.2f * sinf(f) + 0.7f;
			}

			//Filled rectangle
			res[i++] = -0.35f;
			res[i++] = -0.2f;
			res[i++] = -0.25f;
			res[i++] = -0.2f;
			res[i++] = -0.35f;
			res[i++] = +0.2f;
			res[i++] = -0.25f;
			res[i++] = +0.2f;

			//Lined rectangle
			res[i++] = +0.9f;
			res[i++] = +0.2f;
			res[i++] = +0.5f;
			res[i++] = +0.2f;
			res[i++] = +0.5f;
			res[i++] = -0.2f;
			res[i++] = +0.9f;
			res[i++] = -0.2f;

			//Arrows
			//Input arrow
			res[i++] = -1.0f;
			res[i++] = -0.0f;
			res[i++] = -0.9f;
			res[i++] = -0.0f;

			res[i++] = -0.9f;
			res[i++] = -0.0f;
			res[i++] = -0.95f;
			res[i++] = -0.05f;

			res[i++] = -0.9f;
			res[i++] = -0.0f;
			res[i++] = -0.95f;
			res[i++] = +0.05f;

			//Wait arrow
			res[i++] = -0.5f;
			res[i++] = -0.0f;
			res[i++] = -0.35f;
			res[i++] = -0.0f;

			res[i++] = -0.35f;
			res[i++] = -0.0f;
			res[i++] = -0.40f;
			res[i++] = -0.05f;

			res[i++] = -0.35f;
			res[i++] = -0.0f;
			res[i++] = -0.40f;
			res[i++] = +0.05f;

			//Processor arrow
			res[i++] = -0.25f;
			res[i++] = -0.0f;
			res[i++] = -0.1f;
			res[i++] = -0.0f;

			res[i++] = -0.1f;
			res[i++] = -0.0f;
			res[i++] = -0.15f;
			res[i++] = -0.05f;

			res[i++] = -0.1f;
			res[i++] = -0.0f;
			res[i++] = -0.15f;
			res[i++] = +0.05f;

			//Execution arrow
			res[i++] = +0.3f;
			res[i++] = -0.0f;
			res[i++] = +0.5f;
			res[i++] = -0.0f;

			res[i++] = +0.5f;
			res[i++] = -0.0f;
			res[i++] = +0.45f;
			res[i++] = -0.05f;

			res[i++] = +0.5f;
			res[i++] = -0.0f;
			res[i++] = +0.45f;
			res[i++] = +0.05f;

			//Output arrow
			res[i++] = +0.9f;
			res[i++] = -0.0f;
			res[i++] = +1.0f;
			res[i++] = -0.0f;

			res[i++] = +1.0f;
			res[i++] = -0.0f;
			res[i++] = +0.95f;
			res[i++] = -0.05f;

			res[i++] = +1.0f;
			res[i++] = -0.0f;
			res[i++] = +0.95f;
			res[i++] = +0.05f;

			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Array_Size, res, GL_STATIC_DRAW);
			std::get<0>(it.second) = true;
		}
}
void Canvas::draw(std::pair<NetType const, NetInfo>& net) {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, std::get<1>(net.second));
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_LINE_LOOP, 0, Circle_Size);
	glDrawArrays(GL_LINE_LOOP, Circle_Size, Circle_Size);
	glDrawArrays(GL_LINE_LOOP, Circle_Size * 2, Circle_Size);
	glDrawArrays(GL_TRIANGLE_STRIP, Circle_Size * Circles, Square_Size);
	glDrawArrays(GL_LINE_LOOP, Circle_Size * Circles + Square_Size, Square_Size);
	glDrawArrays(GL_LINES, Circle_Size * Circles + Square_Size * Squares, Straight_Arrows * Straight_Arrow_Size);
	glDisableVertexAttribArray(0);
}