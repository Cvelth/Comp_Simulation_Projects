#pragma once

namespace cs {
	enum class SimulationState {
		Running = 1, Paused = 2, Stoped = 3, Error = 0
	};
	using number = float;

	namespace constants {
		const number time_correction = 1;
	}
}