#include "SimulatorUnit.hpp"
#include <thread>
#include <random>
#include "AbstractStorage.hpp"

void qs::GeneratorUnit::loop() {
	std::thread t([this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::poisson_distribution<number> *d = nullptr;
		m_current_process_start = std::chrono::high_resolution_clock::now();
		while (*m_state == SystemState::Running || *m_state == SystemState::Paused)
			if (*m_state == SystemState::Running) {
				if (!d || d->mean() != m_lambda)
					d = new std::poisson_distribution<number>(m_lambda);
				auto duration = std::chrono::duration<float>(*m_time_coefficient *
															 qs::constants::time_correction * (*d)(g));
				m_current_process_end = m_current_process_start + duration;
				m_current_task = *(new Task());
				m_is_active = true;
				std::this_thread::sleep_until(m_current_process_end);
				m_current_process_start = std::chrono::high_resolution_clock::now();
				m_storage->push(&m_current_task);
			}
	});
	t.detach();
}

float qs::GeneratorUnit::getCurrentPercent() {
	if (m_is_active)
		return (std::chrono::high_resolution_clock::now() - m_current_process_start) * 1000 /
		(m_current_process_end - m_current_process_start);
	else
		return 0.f;
}