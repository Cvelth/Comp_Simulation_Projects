#include "TaskProcessor.hpp"
#include <thread>
#include <chrono>
#include <random>

void cs::TaskProcessor::loop() {
	std::thread t([this]() {
		m_current_processing_start = std::chrono::high_resolution_clock::now();
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::normal_distribution<number> *d = nullptr;
		m_is_processing = true;
		while (*m_state == SimulationState::Running || *m_state == SimulationState::Paused)
			if (*m_state == SimulationState::Running) {
				m_current_task = m_storage->pop_default(Task(0.f, m_tau));
				float wait = m_current_task.processing_left();
				if (wait == 0.f) {
					if (!d)
						d = new std::normal_distribution<number>(m_mu, m_sigma);
					else if (d->mean() != m_mu || d->sigma() != m_sigma) {
						delete d;
						d = new std::normal_distribution<number>(m_mu, m_sigma);
					}
					wait = (*d)(g);
				}

				float processing_left = wait - m_tau;
				bool repush = processing_left > 0.f;
				float scale = cs::constants::time_correction * *m_time_coefficient;
				float scaled_wait = scale * wait;
				float scaled_tau = scale * m_tau;
				time_point m_current_processing_step = m_current_processing_start;
				if (repush)
					m_current_processing_step += std::chrono::duration<float>(scaled_tau);
				else
					m_current_processing_step += std::chrono::duration<float>(scaled_wait);

				m_current_processing_end = m_current_processing_start + 
					std::chrono::duration<float>(scaled_wait);
				m_current_processing_start -= 
					std::chrono::duration<float>(scaled_tau * m_current_task.was_processed());

				std::this_thread::sleep_until(m_current_processing_step);
				m_current_processing_start = std::chrono::high_resolution_clock::now();

				if (repush) {
					m_current_task.set_processing_left(processing_left);
					m_current_task.process();
					m_storage->repush(&m_current_task);
				} else
					if (++m_executed_count == 100)
						*m_state = SimulationState::Paused;
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

cs::Color cs::TaskProcessor::getCurrentColor() {
	if (m_is_processing)
		return m_current_task.color();
	else
		return Color{0,0,0};
}

size_t cs::TaskProcessor::getExecutedCount() {
	return m_executed_count;
}

bool cs::TaskProcessor::is_running() {
	return *m_state == SimulationState::Running;
}
