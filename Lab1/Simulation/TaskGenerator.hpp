#pragma once
#include "Shared.hpp"

namespace cs {
	class TaskStorage;

	class TaskGenerator {
		SimulationState m_state;
		number m_lambda;
		TaskStorage *m_storage;
	protected:
		void loop();
	public:
		TaskGenerator(TaskStorage *storage) : m_storage(storage) {}
		inline void start() {
			if (m_state != SimulationState::Error)
				m_state = SimulationState::Running;
			loop();
		}
		inline void pause() {
			if (m_state == SimulationState::Running)
				m_state = SimulationState::Paused;
			else if (m_state == SimulationState::Paused)
				m_state = SimulationState::Running;
		}
		inline void stop() {
			if (m_state != SimulationState::Error)
				m_state = SimulationState::Stoped;
		}
	};
}