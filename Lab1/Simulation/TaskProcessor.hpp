#pragma once
#include "Shared.hpp"

namespace cs {
	class TaskStorage;

	class TaskProcessor {
		SimulationState m_state;
		number m_mu;
		number m_sigma;
		number m_tau;
		TaskStorage *m_storage;
		number *m_time_coefficient;
	protected:
		void loop();
	public:
		TaskProcessor(TaskStorage *storage, number *time_coefficient) 
			: m_storage(storage), m_time_coefficient(time_coefficient) {}
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
		inline void changeMu(number m) {
			m_mu = m;
		}
		inline void changeSigma(number s) {
			m_sigma = s;
		}
		inline void changeTau(number t) {
			m_tau = t;
		}
	};
}