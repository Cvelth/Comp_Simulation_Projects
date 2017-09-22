#include "TaskStorage.hpp"
#include <random>

std::mt19937_64 g;
std::uniform_real_distribution<float> d(0.f, 1.f);

cs::Task::Task() {
	m_color = Color{d(g), d(g), d(g)};
}
