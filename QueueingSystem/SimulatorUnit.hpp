#pragma once
#include "ExecutionUnit.hpp"
#include <chrono>
namespace qs {
	using time_point = std::chrono::time_point<std::chrono::high_resolution_clock,
		std::chrono::duration<float, std::ratio<1, 1000000000>>>;

	class SimulatorUnit : public ExecutionUnit {
	protected:
		time_point m_current_generation_start;
		time_point m_current_generation_end;

	};
}