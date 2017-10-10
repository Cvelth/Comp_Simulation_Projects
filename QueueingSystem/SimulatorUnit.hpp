#pragma once
#include "ExecutionUnit.hpp"
#include <chrono>
namespace qs {
	using time_point = std::chrono::time_point<std::chrono::high_resolution_clock,
		std::chrono::duration<float, std::ratio<1, 1000000000>>>;

	class SimulatorUnit : public ExecutionUnit {
	protected:
		number *m_time_coefficient;
		time_point m_current_process_start;
		time_point m_current_process_end;
	public:
		explicit SimulatorUnit(AbstractStorage* storage, number *time_coefficient, SystemState *state)
			: ExecutionUnit(storage, state), m_time_coefficient(time_coefficient) {}
	};

	class GeneratorSimulator : public SimulatorUnit, public GeneratorUnit {
	protected:
		virtual void loop() override;
	public:
		using SimulatorUnit::SimulatorUnit;
		virtual bool is_running() override {
			return *m_state == SystemState::Running;
		}
		virtual void start() override { SimulatorUnit::start(); }
		virtual void pause() override { SimulatorUnit::pause(); }
		virtual void stop() override { SimulatorUnit::stop(); }
		virtual qs::Color const getCurrentColor() override { return SimulatorUnit::getCurrentColor(); }
		virtual float getCurrentPercent() override;
	};

	class ProcessorSimulator : public SimulatorUnit, public ProcessorUnit {
	protected:
		virtual void loop() override;
	public:
		using SimulatorUnit::SimulatorUnit;
		virtual bool is_running() override {
			return *m_state == SystemState::Running;
		}
		virtual void start() override { SimulatorUnit::start(); }
		virtual void pause() override { SimulatorUnit::pause(); }
		virtual void stop() override { SimulatorUnit::stop(); }
		virtual qs::Color const getCurrentColor() override { return SimulatorUnit::getCurrentColor(); }
		virtual float getCurrentPercent() override;
	};
}