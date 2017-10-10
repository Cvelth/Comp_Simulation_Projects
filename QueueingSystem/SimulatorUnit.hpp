#pragma once
#include "ExecutionUnit.hpp"
#include <chrono>
namespace qs {
	using time_point = std::chrono::time_point<std::chrono::high_resolution_clock,
		std::chrono::duration<float, std::ratio<1, 1000000000>>>;

	class SimulatorUnit : public ExecutionUnit {
	protected:
		time_point m_current_process_start;
		time_point m_current_process_end;
	public:
		using ExecutionUnit::ExecutionUnit;
	};

	class GeneratorUnit : public SimulatorUnit {
		number m_lambda;
	protected:
		void loop() override;
	public:
		using SimulatorUnit::SimulatorUnit;
		virtual float getCurrentPercent() override;
		inline void changeLambda(number l) { m_lambda = l; }
	};

	class ProcessorUnit : public SimulatorUnit {
		number m_mu;
		number m_sigma;
		number m_tau;
	protected:
		void loop() override;
	public:
		using SimulatorUnit::SimulatorUnit;
		virtual float getCurrentPercent() override;
		inline void changeMu(number m) { m_mu = m; }
		inline void changeSigma(number s) { m_sigma = s; }
		inline void changeTau(number t) { m_tau = t; }
	};
}