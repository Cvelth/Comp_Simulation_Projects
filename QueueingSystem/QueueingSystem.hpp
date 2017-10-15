#pragma once
#define MULTI_THREADING
#include "shared.hpp"
#include "AbstractStorage.hpp"
#include "ExecutionUnit.hpp"
#include "LIFO.hpp"
#include "PER.hpp"
#include "TaskSimulation.hpp"
#include "TaskImitation.hpp"

namespace qs {
	enum class SystemType {
		LIFO, PER
	};

	template <typename Task>
	class AbstractQueueingSystem {
	protected:
		SystemState m_state;
		AbstractStorage<Task> *m_storage;
	public:
		AbstractQueueingSystem() :
			m_state(qs::SystemState::Stoped) {}
		AbstractQueueingSystem(SystemType type) :
			AbstractQueueingSystem() {
			initialize(type);
		}

		virtual void initialize(SystemType type) abstract;

		virtual void changeLambda(number l) abstract;
		virtual void changeMu(number m) abstract;
		virtual void changeSigma(number s) abstract;
		virtual void changeTau(number t) abstract;

		virtual bool is_running() abstract;
		SystemType type() {
			auto t = m_storage->type();
			switch (t) {
				case 1:	return SystemType::LIFO;
				case 2:	return SystemType::PER;
				default: throw std::exception("Unsupported storage type was requested");
			}
		}
		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) { m_storage->for_each_push(lambda); }
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) { m_storage->for_each_repush(lambda);	}
	};

	class QueueingSystemSimulation : public AbstractQueueingSystem<TaskSimulation> {
		GeneratorUnit *m_generator;
		ProcessorUnit *m_processor;
		number m_time_coefficient;
	public:
		using AbstractQueueingSystem<TaskSimulation>::AbstractQueueingSystem;

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
        
		virtual void changeLambda(number l) override { m_generator->changeLambda(l); }
		virtual void changeMu(number m) override { m_processor->changeMu(m); }
		virtual void changeSigma(number s) override { m_processor->changeSigma(s); }
		virtual void changeTau(number t) override { m_processor->changeTau(t); }

		virtual GeneratorUnit* generator() { return m_generator; }
		virtual ProcessorUnit* processor() { return m_processor; }

		virtual bool is_running() override {
			return m_generator->is_running() && m_processor->is_running();
		}
		void changeTimeCoefficient(number c) { m_time_coefficient = c; }
	};
	class ImitationStatistics;
	class QueueingSystemImitation : public AbstractQueueingSystem<qs::TaskImitation> {
		number m_lambda;
		number m_mu;
		number m_sigma;
		number m_tau;
	public:
		using AbstractQueueingSystem::AbstractQueueingSystem;
		virtual void initialize(SystemType type) override;
		void run(size_t tasks, ImitationStatistics *stats = nullptr, bool detach = true);

		virtual void changeLambda(number l) override { m_lambda = l; }
		virtual void changeMu(number m) override { m_mu = m; }
		virtual void changeSigma(number s) override { m_sigma = s; }
		virtual void changeTau(number t) override { m_tau = t; }
		virtual bool is_running() override { return false; }

	};
}