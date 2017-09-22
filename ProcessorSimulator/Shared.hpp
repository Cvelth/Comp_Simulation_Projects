#pragma once
#include <chrono>

namespace cs {
	enum class SimulationState {
		Running = 1, Paused = 2, Stoped = 3, Error = 0
	};
	using number = float;
	struct Color {
		number r;
		number g;
		number b;
	};
	using time_point = std::chrono::time_point<std::chrono::high_resolution_clock, 
		std::chrono::duration<float, std::ratio<1, 1000000000>>>;

	namespace constants {
		const number time_correction = 1;
	}
}