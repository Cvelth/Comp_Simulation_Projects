#pragma once
#include "shared.hpp" 
#include "Task.hpp"
namespace qs {
	class AbstractStorage;
	class ExecutionUnit {
	protected:
		SystemState *m_state;
		AbstractStorage *m_storage;
		number *m_time_coefficient;
		bool m_is_active;
		Task m_current_task;
		size_t m_task_count;
	protected:
		virtual void loop() abstract;
	public:
		explicit ExecutionUnit(AbstractStorage* storage, number *time_coefficient, SystemState *state)
			: m_storage(storage), m_time_coefficient(time_coefficient), m_state(state),
			m_is_active(false), m_task_count(0u) {}

		inline void start() {
			if (*m_state != SystemState::Error)
				*m_state = SystemState::Running;
			loop();
		}
		inline void pause() {
			if (*m_state == SystemState::Running)
				*m_state = SystemState::Paused;
			else if (*m_state == SystemState::Paused)
				*m_state = SystemState::Running;
		}
		inline void stop() {
			if (*m_state != SystemState::Error)
				*m_state = SystemState::Stoped;
		}
		inline bool is_active() {
			return m_is_active;
		}
		inline size_t getTaskCount() {
			return m_task_count;
		}
		inline Color getCurrentColor() {
			return m_current_task.color();
		}
		virtual float getCurrentPercent() abstract;
	};
}