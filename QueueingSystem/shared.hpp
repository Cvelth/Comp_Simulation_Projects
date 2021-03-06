#pragma once
#include <exception>
namespace qs {
	enum class SystemState {
		Running = 1, Paused = 2, Stoped = 3, Error = 0
	};
	using number = float;
	struct Color {
		number r;
		number g;
		number b;
	};
	namespace Exceptions {
		class EmptyQueue : std::exception {};
	}
	namespace constants {
		const number time_correction = 1;
	}
}