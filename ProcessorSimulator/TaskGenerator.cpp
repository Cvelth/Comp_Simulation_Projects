#include "TaskGenerator.hpp"
#include "TaskStorage.hpp"
#include <thread>
#include <chrono>
#include <random>

void cs::TaskGenerator::loop() {
	std::thread t([this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::poisson_distribution<number> *d = nullptr;
		while (m_state == SimulationState::Running || m_state == SimulationState::Paused) 
			if (m_state == SimulationState::Running) {
				if (!d || d->mean() != m_lambda)
					d = new std::poisson_distribution<number>(m_lambda);
				m_current_generation_start = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration<float>(*m_time_coefficient * 
															 cs::constants::time_correction * (*d)(g));
				m_current_generation_end = m_current_generation_start + duration;
				m_current_task = new Task();
				m_is_generating = true;
				std::this_thread::sleep_for(duration);
				m_storage->push(m_current_task);
			}
	});
	t.detach();
}

float cs::TaskGenerator::getCurrentPercent() {
	if (m_is_generating)
		return (std::chrono::high_resolution_clock::now() - m_current_generation_start) * 1000 / 
		(m_current_generation_end - m_current_generation_start);
	else
		return 0.f;
}

cs::Color const& cs::TaskGenerator::getCurrentColor() {
	if (m_is_generating)
		return m_current_task->color();
	else
		return Color{0,0,0};
}

bool cs::TaskGenerator::is_running() {
	return m_state == SimulationState::Running;
}
