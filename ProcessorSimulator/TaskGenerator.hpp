#pragma once
#include "Shared.hpp"
#include <chrono>

namespace cs {
	class Task;
	class TaskStorage;
	class TaskGenerator {
		SimulationState m_state;
		number m_lambda;
		TaskStorage *m_storage;
		number *m_time_coefficient;
		time_point m_current_generation_start;
		time_point m_current_generation_end;
		bool m_is_generating;
		Task *m_current_task;
	protected:
		void loop();
	public:
		TaskGenerator(TaskStorage *storage, number *time_coefficient)
			: m_storage(storage), m_time_coefficient(time_coefficient), 
			m_state(SimulationState::Stoped), m_is_generating(false) {}
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
		inline void changeLambda(number l) {
			m_lambda = l;
		}
		float getCurrentPercent();
		Color const& getCurrentColor();
	};
}