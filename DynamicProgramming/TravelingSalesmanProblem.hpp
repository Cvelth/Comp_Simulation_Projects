#pragma once
#include <vector>
namespace dp {
	using City = size_t;
	using Distance = float;
	namespace TravelingSalesmanProblem {
		std::vector<City> solve(std::vector<std::vector<float>> &input_matrix);
	}
}