#pragma once
#include <vector>
namespace arc_math {
	using number = float;
	struct point {
		number x, y;
	};
	std::vector<number> generate(point const& s, point const& e, size_t const accuracy = 20ull);
}