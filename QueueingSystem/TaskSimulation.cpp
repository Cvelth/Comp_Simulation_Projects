#include "TaskSimulation.hpp"
#include <random>

std::mt19937_64 g;
std::uniform_real_distribution<float> d(0.f, 1.f);

qs::TaskSimulation::TaskSimulation(float expiration, float color, float processing_left) : m_processing_left(0.f), m_was_processed(0), m_expiration(expiration), m_creation_time(std::chrono::high_resolution_clock::now()) {
	if (color < 0.f || color > 1.f)
		m_color = Color{d(g), d(g), d(g)};
	else
		m_color = Color{0.95f, 0.75f, 0.95f};
}
bool qs::TaskSimulation::is_expired() const {
	auto dur = std::chrono::high_resolution_clock::now() - m_creation_time;
	auto exp = std::chrono::nanoseconds(size_t(m_expiration * 1e9));
	auto b = dur > exp;
	return m_expiration != 0.f && std::chrono::high_resolution_clock::now() - m_creation_time > std::chrono::nanoseconds(size_t(m_expiration * 1e9));
}
