#include "ArcMath.hpp"
std::vector<arc_math::number> arc_math::generate(point const& s, point const& e, size_t const accuracy) {
	return std::vector<number>{s.x, s.y, e.x, e.y};
}