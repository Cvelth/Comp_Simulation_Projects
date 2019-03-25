#include "TaskSimulation.hpp"
#include <random>

std::mt19937_64 g;
std::uniform_real_distribution<float> d(0.f, 1.f);

qs::TaskSimulation::TaskSimulation(float color, float processing_left, std::chrono::high_resolution_clock::time_point expiration_time) : m_processing_left(0.f), m_was_processed(0), m_expiration_time(expiration_time) {
	if (color < 0.f || color > 1.f)
		m_color = Color{d(g), d(g), d(g)};
	else
		m_color = Color{0.95f, 0.75f, 0.95f};
}
