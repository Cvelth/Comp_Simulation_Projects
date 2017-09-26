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
				m_current_processing_start = std::chrono::high_resolution_clock::now();

				try {
					m_current_task = m_storage->pop();
				} catch (cs::Exceptions::EmptyQueue) {
					m_current_task = Task(0.f);
					m_current_task.set_processing_left(m_tau);
				}
				float wait = m_current_task.processing_left();
				if (wait == 0.f) {
					if (!d || d->mean() != m_mu || d->sigma() != m_sigma)
						d = new std::normal_distribution<number>(m_mu, m_sigma);
					wait = (*d)(g);
				}

				float processing_left = wait - m_tau;
				bool repush = processing_left > 0.f;
				std::chrono::duration<float> duration =
					std::chrono::duration<float>(cs::constants::time_correction *
												 *m_time_coefficient *
												 (repush ? m_tau : wait));
				auto m_current_processing_step = m_current_processing_start + duration;

				m_current_processing_end = m_current_processing_start +
					std::chrono::duration<float>(cs::constants::time_correction *
												 *m_time_coefficient * wait);
				m_current_processing_start -=
					std::chrono::duration<float>(cs::constants::time_correction *
												 *m_time_coefficient * m_tau *
												 m_current_task.was_processed());
				m_is_processing = true;

				std::this_thread::sleep_until(m_current_processing_step);
				if (repush) {
					m_current_task.set_processing_left(processing_left);
					m_current_task.process();
					m_storage->repush(&m_current_task);
				}
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

bool cs::TaskProcessor::is_running() {
	return m_state == SimulationState::Running;
}
