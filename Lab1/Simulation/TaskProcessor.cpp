#include "TaskProcessor.hpp"
#include "TaskStorage.hpp"
#include <thread>
#include <chrono>
#include <random>

void cs::TaskProcessor::loop() {
	std::thread t([this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::normal_distribution<float> *d;
		while (m_state == SimulationState::Running || m_state == SimulationState::Paused)
			if (m_state == SimulationState::Running) {
				if (!d || d->mean() != m_mu || d->sigma() != m_sigma)
					d = new std::normal_distribution<float>(m_mu, m_sigma);
				auto wait = (*d)(g);
				m_storage->pop();
				std::this_thread::sleep_for(std::chrono::duration<float>(
					* m_time_coefficient * cs::constants::time_correction * wait));
		}
	});
	t.detach();
}
