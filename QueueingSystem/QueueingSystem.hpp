#pragma once
#include "shared.hpp"
#include "AbstractStorage.hpp"
#include "ExecutionUnit.hpp"

namespace qs {
	enum class SystemType {
		LIFO, PER
	};

	class AbstractQueueingSystem {
	protected:
		SystemState m_state;
		GeneratorUnit *m_generator;
		AbstractStorage *m_storage;
		ProcessorUnit *m_processor;
	protected:
		void initializeStorage(SystemType type);
	public:
		AbstractQueueingSystem() :
			m_state(qs::SystemState::Stoped) {}
		AbstractQueueingSystem(SystemType type) :
			AbstractQueueingSystem() {
			initialize(type);
		}

		virtual void initialize(SystemType type) abstract;

		void changeLambda(number l) {m_generator->changeLambda(l);}
		void changeMu(number m) { m_processor->changeMu(m); }
		void changeSigma(number s) { m_processor->changeSigma(s); }
		void changeTau(number t) { m_processor->changeTau(t); }

		inline GeneratorUnit* generator() { return m_generator; }
		inline AbstractStorage* storage() { return m_storage; }
		inline ProcessorUnit* processor() { return m_processor; }

		inline bool is_running() {
			return m_generator->is_running() && m_processor->is_running();
		}
		SystemType type();
	};

	class QueueingSystemSimulation : public AbstractQueueingSystem {
		number m_time_coefficient;
	public:
		using AbstractQueueingSystem::AbstractQueueingSystem;
		virtual void initialize(SystemType type) override;
		void start() {
			m_generator->start();
			m_processor->start();
		}
		void pause() {
			m_generator->pause();
			m_processor->pause();
		}
		void stop() {
			m_generator->stop();
			m_processor->stop();
		}
		void changeTimeCoefficient(number c) { m_time_coefficient = c; }
	};
	class QueueingSystemImitation : public AbstractQueueingSystem {
		number m_time_coefficient;
	public:
		using AbstractQueueingSystem::AbstractQueueingSystem;
		virtual void initialize(SystemType type) override;
		void run(size_t tasks);
	};
}