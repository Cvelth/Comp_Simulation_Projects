#include "TaskProcessor.hpp"
#include <thread>
#include <chrono>

void cs::TaskProcessor::loop() {
	std::thread t([this]() {
		while (m_state == SimulationState::Running || m_state == SimulationState::Paused)
			if (m_state == SimulationState::Running) {
			//Process tasks.
		}
	});
	t.join();
}
