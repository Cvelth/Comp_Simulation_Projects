#pragma once
namespace task {
	float const sigma = 1.f;

	float const k1 = -5.f;
	float const k2 = -4.f;
	float const k3 = -2.f;
	float const k4 = +3.f;
	float const k5 = +1.f;

	float const t1 = 3.f;
	float const t2 = 3.f;

	inline float const f(float const x1, float const x2, float const x3, float const x4, float const x5) {
		return x1 * k1 + x2 * k2 + x3 * k3 + x4 * k4 + x5 * k5;
	}
}