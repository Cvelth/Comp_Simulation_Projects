#include "TaskProcessor.hpp"
#include <thread>
#include <chrono>
#include <random>

void cs::TaskProcessor::loop() {
	std::thread t([this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::normal_distribution<number> *d = nullptr;
		while (m_state == SimulationState::Running || m_state == SimulationState::Paused)
			if (m_state == SimulationState::Running) {
				if (!d || d->mean() != m_mu || d->sigma() != m_sigma)
					d = new std::normal_distribution<number>(m_mu, m_sigma);
				try {
					m_current_task = m_storage->pop();
				} catch (cs::Exceptions::EmptyQueue) {
					m_current_task = Task(0.f);
				}

				m_current_processing_start = std::chrono::high_resolution_clock::now();
				auto wait = *m_time_coefficient * cs::constants::time_correction * (*d)(g);
				auto duration = std::chrono::duration<float>(wait);
				m_current_processing_end = m_current_processing_start + duration;
				m_is_processing = true;
				std::this_thread::sleep_for(duration);
		}
	});
	t.detach();
}

float cs::TaskProcessor::getCurrentPercent() {
	if (m_is_processing)
		return (std::chrono::high_resolution_clock::now() - m_current_processing_start) * 1000 /
		(m_current_processing_end - m_current_processing_start);
	else
		return 0.f;
}

cs::Color const& cs::TaskProcessor::getCurrentColor() {
	if (m_is_processing)
		return m_current_task.color();
	else
		return Color{0,0,0};
}