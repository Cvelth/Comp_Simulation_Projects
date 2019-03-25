#include "SimulatorUnit.hpp"
#include <thread>
#include <random>
#include <chrono>
#include "AbstractStorage.hpp"

void qs::GeneratorSimulator::loop() {
	std::thread t([this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::poisson_distribution<number> *d = nullptr;
		std::normal_distribution<number> *n_d = new std::normal_distribution<number>(m_expiration, 1.f);
		//m_current_process_start = std::chrono::high_resolution_clock::now();
		while (*m_state == SystemState::Running || *m_state == SystemState::Paused)
			if (*m_state == SystemState::Running) {
				if (!d || d->mean() != m_lambda)
					d = new std::poisson_distribution<number>(m_lambda);
				auto duration = std::chrono::duration<float>(*m_time_coefficient *
															 qs::constants::time_correction * (*d)(g));
				if (n_d->mean() != m_expiration || n_d->sigma() != 1.f) {
					delete n_d;
					n_d = new std::normal_distribution<number>(m_expiration, 1.f);
				}
				m_current_task = *(new TaskSimulation((*n_d)(g)));
				m_current_process_start = std::chrono::high_resolution_clock::now();
				m_current_process_end = m_current_process_start + duration;
				m_is_active = true;
				std::this_thread::sleep_until(m_current_process_end);
				m_is_active = false;
				m_storage->push(&m_current_task);
				for (auto &storage : m_additional_storage)
					storage->push(new TaskSimulation(m_current_task));
				//m_current_process_start = std::chrono::high_resolution_clock::now();
			}
	});
	t.detach();
}

float qs::GeneratorSimulator::getCurrentPercent() {
	if (m_is_active)
		return (std::chrono::high_resolution_clock::now() - m_current_process_start) /
			(m_current_process_end - m_current_process_start);
	else
		return 0.f;
}