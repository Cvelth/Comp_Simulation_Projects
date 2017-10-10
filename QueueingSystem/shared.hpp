#pragma once
#include <exception>
//#define MULTI_THREADING

namespace qs {
	using number = float;
	struct Color {
		number r;
		number g;
		number b;
	};
	namespace Exceptions {
		class EmptyQueue : std::exception {};
	}
}