#include "TaskStorage.hpp"
#include <random>

std::mt19937_64 g;
std::uniform_real_distribution<float> d(0.f, 1.f);

cs::Task::Task(float color, float processing_left) : m_processing_left(0.f), m_was_processed(0) {
	if (color < 0.f || color > 1.f)
		m_color = Color{d(g), d(g), d(g)};
	else
		m_color = Color{0.95f, 0.75f, 0.95f};
}
