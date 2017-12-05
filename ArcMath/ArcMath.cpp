#include <cmath>
#include "ArcMath.hpp"
using namespace arc_math;
const float pi = std::atanf(1.f) * 4.f;
point operator+(point const& s, point const& e) {
	return point{e.x + s.x, e.y + s.y};
}
point operator-(point const& s, point const& e) {
	return point{e.x - s.x, e.y - s.y};
}
point middle(point const& s, point const& e) {
	return point{(s.x + e.x) / 2, (s.y + e.y) / 2};
}
number operator*(point const& p) {
	return sqrtf(p.x * p.x + p.y * p.y);
}
point operator*(point const& p, number const& n) {
	return point{p.x * n, p.y * n};
}
point operator/(point const& p, number const& n) {
	return point{p.x / n, p.y / n};
}
point operator!(point const& p) {
	return point{p.y, -p.x};
}
point operator~(point const& p) {
	return p / *p;
}
number operator*(point const& s, point const& e) {
	return s.x * e.x + s.y * e.y;
}
std::vector<number> arc_math::generate(point const& s, point const& e, size_t const accuracy) {
	std::vector<number> arc;

	point se = e - s;
	point c = middle(s, e);
	point n = ~!se;
	point o = c + n * *se;

	point os = s - o;
	point oe = e - o;

	number r = *os;

	number am = acosf(~os * ~oe);
	number as = acosf(~os * point{1, 0});
	float step = am / accuracy;

	for (float f = 0.f; f <= am; f += step) {
		if (s.y < o.y) {
			arc.push_back(-r * cosf(f + as) + o.x);
			arc.push_back(-r * sinf(f + as) + o.y);
		} else {
			arc.push_back(-r * cosf(f + as -am) + o.x);
			arc.push_back(r * sinf(f + as - am) + o.y);
		}
	}
	return arc;
}