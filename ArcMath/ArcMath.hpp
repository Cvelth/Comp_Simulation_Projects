#pragma once
#ifdef _WIN32
	#ifdef INTERPRETER_EXPORTS
		#define DLL __declspec(dllexport)
	#else
		#define DLL __declspec(dllimport)
	#endif
#else
	#define DLL
#endif

#include <vector>
namespace arc_math {
	using number = float;
	struct point {
		number x, y;
	};
	/*
		the function for generation of an Arc with given start (s) and end (e) points.
		(q) determines the coefficient of radius dependent on distance between the points.
		(accuracy) shows how many lines will be returned from the function.
		return points are inserted into std::vector.
	*/
	DLL std::vector<number> generate_p(point const& s, point const& e, float q = 1.f, size_t const accuracy = 20ull);
	/*
		the function for generation of an Arc with given start (sx and sy coordinates) and end (ex and ey coordinates) points.
		(q) determines the coefficient of radius dependent on distance between the points.
		(accuracy) shows how many lines will be returned from the function.
		return points are inserted into std::vector.
	*/
	inline std::vector<number> generate(number const& sx, number const& sy, number const& ex, number const& ey, float q = 1.f, size_t const accuracy = 20ull) {
		return generate_p(point{sx, sy}, point{ex,ey}, q, accuracy);
	}
}