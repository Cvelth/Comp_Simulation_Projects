#include "TaskGenerator.hpp"
#include <thread>
#include <chrono>

void cs::TaskGenerator::loop() {
	std::thread t([this]() {
		while (m_state == SimulationState::Running || m_state == SimulationState::Paused) 
			if (m_state == SimulationState::Running) {
			//Generate tasks.
		}
	});
	t.join();
}