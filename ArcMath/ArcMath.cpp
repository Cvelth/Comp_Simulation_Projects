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
std::vector<number> arc_math::generate(point const& s, point const& e, float q, size_t const accuracy) {
	std::vector<number> arc;

	point o = middle(s, e) + !(e - s) * q;
	point os = s - o;
	number r = *os;

	number am = acosf(~os * ~(e - o));
	number as = acosf(~os * point{1, 0});
	float step = am / accuracy;

	float d = (s.y > o.y) ? am : 0.f;
	float m = (s.y > o.y) ? 1.f : -1.f;
	for (float f = 0.f; f <= am; f += step) {
			arc.push_back(-r * cosf(f + as - d) + o.x);
			arc.push_back(m * r * sinf(f + as - d) + o.y);
	}
	if (s.y < o.y) {
		arc.push_back(e.x);
		arc.push_back(e.y);
	} else {
		arc.push_back(s.x);
		arc.push_back(s.y);
	}
	return arc;
}