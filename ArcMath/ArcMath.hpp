#pragma once
#include <vector>
namespace arc_math {
	using number = float;
	struct point {
		number x, y;
	};
	std::vector<number> generate(point const& s, point const& e, size_t const accuracy = 20ull);
	inline std::vector<number> generate(number const& sx, number const& sy, number const& ex, number const& ey, size_t const accuracy = 20ull) {
		return generate(point{sx, sy}, point{ex,ey}, accuracy);
	}
}