#pragma once
#include "shared.hpp" 
#include "Task.hpp"
namespace qs {
	class AbstractStorage;
	class ExecutionUnit {
	protected:
		SystemState *m_state;
		AbstractStorage *m_storage;
		bool m_is_active;
		Task m_current_task;
		size_t m_task_count;
	protected:
		virtual void loop() abstract;
	public:
		explicit ExecutionUnit(AbstractStorage* storage, SystemState *state)
			: m_storage(storage), m_state(state),
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
			if (is_active())
				return m_current_task.color();
			else
				return Color{0,0,0};
		}
		virtual float getCurrentPercent() abstract;
	};

	class GeneratorUnit {
	protected:
		number m_lambda;
	public:
		virtual bool is_running() abstract;
		inline void changeLambda(number l) { m_lambda = l; }

		virtual void start() abstract;
		virtual void pause() abstract;
		virtual void stop() abstract;
	};
	class ProcessorUnit {
	protected:
		number m_mu;
		number m_sigma;
		number m_tau;
	public:
		virtual bool is_running() abstract;
		inline void changeMu(number m) { m_mu = m; }
		inline void changeSigma(number s) { m_sigma = s; }
		inline void changeTau(number t) { m_tau = t; }

		virtual void start() abstract;
		virtual void pause() abstract;
		virtual void stop() abstract;
	};
}