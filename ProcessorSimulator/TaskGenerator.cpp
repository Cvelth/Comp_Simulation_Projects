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
				auto wait = *m_time_coefficient * cs::constants::time_correction *(*d)(g);
				std::this_thread::sleep_for(std::chrono::duration<number>(wait));
				m_storage->push();
			}
	});
	t.detach();
}