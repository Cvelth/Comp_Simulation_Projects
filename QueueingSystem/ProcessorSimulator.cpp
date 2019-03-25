#include "SimulatorUnit.hpp"
#include "AbstractStorage.hpp"
#include <thread>
#include <chrono>
#include <random>

void qs::ProcessorSimulator::loop() {
	std::thread t([this]() {
		m_current_process_start = std::chrono::high_resolution_clock::now();
		std::mt19937_64 g(std::random_device{}());
		std::normal_distribution<number> *d = nullptr;
		m_is_active = true;
		while (*m_state == SystemState::Running || *m_state == SystemState::Paused)
			if (*m_state == SystemState::Running) {
				m_current_task = m_storage->pop_default(TaskSimulation(0.f, m_tau));
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
				float scale = qs::constants::time_correction * *m_time_coefficient;
				float scaled_wait = scale * wait;
				float scaled_tau = scale * m_tau;
				time_point m_current_processing_step = m_current_process_start;
				if (repush)
					m_current_processing_step += std::chrono::duration<float>(scaled_tau);
				else
					m_current_processing_step += std::chrono::duration<float>(scaled_wait);

				m_current_process_end = m_current_process_start +
					std::chrono::duration<float>(scaled_wait);
				m_current_process_start -=
					std::chrono::duration<float>(scaled_tau * m_current_task.was_processed());

				if (std::chrono::high_resolution_clock::now() < m_current_processing_step)
					std::this_thread::sleep_until(m_current_processing_step);
				m_current_process_start = std::chrono::high_resolution_clock::now();

				if (repush) {
					m_current_task.set_processing_left(processing_left);
					m_current_task.process();
					m_storage->repush(&m_current_task);
				} else {
					m_task_count++;
				}
			}
	});
	t.detach();
}

float qs::ProcessorSimulator::getCurrentPercent() {
	if (m_is_active)
		return (std::chrono::high_resolution_clock::now() - m_current_process_start) * 1000 /
		(m_current_process_end - m_current_process_start);
	else
		return 0.f;
}