#include "ArcMath.hpp"
using namespace arc_math;
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
	return point{-p.x, p.y} / *p;
}
point operator~(point const& p) {
	return p / *p;
}
number operator*(point const& s, point const& e) {
	return s.x * e.x + s.y * e.y;
}
std::vector<number> generate(point const& s, point const& e, size_t const accuracy) {
	 point se = e - s;
	 point c = middle(s, e);
	 point n = !se;
	 point o = c + n * *se;

	 point os = s - o;
	 point oe = e - o;

	 point i{1, 0};
	 number as = ~os * i;
	 number ae = ~oe * i;

	return std::vector<number>{s.x, s.y, e.x, e.y};
}