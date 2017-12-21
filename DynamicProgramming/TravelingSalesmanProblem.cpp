#include "TravelingSalesmanProblem.hpp"
#include <map>
#include <algorithm>
#include <numeric>
std::map<std::vector<dp::TravelingSalesmanProblem::City>, float>& merge(std::map<std::vector<dp::TravelingSalesmanProblem::City>, float> &first, std::map<std::vector<dp::TravelingSalesmanProblem::City>, float> second) {
	for (auto it : second) {
		if (first.find(it.first) == first.end())
			first.insert(it);
		else if (first[it.first] < it.second)
			first[it.first] = it.second;
	}
	return first;
}
std::map<std::vector<dp::TravelingSalesmanProblem::City>, float> solveTSP_inner(std::vector<dp::TravelingSalesmanProblem::City> current, float weight, size_t cities, std::vector<std::vector<dp::TravelingSalesmanProblem::Distance>> const& inputs) {
	if (current.size() == cities)
		return {std::make_pair(current, weight)};

	std::map<std::vector<dp::TravelingSalesmanProblem::City>, float> res;
	auto next = current;
	next.push_back(0);
	for (size_t i = 0; i < cities; i++) {
		if (inputs[current.back()][i] != 0.f && std::find(current.begin(), --current.end(), i) == --current.end()) {
			next.back() = i;
			merge(res, solveTSP_inner(next, weight + inputs[current.back()][i], cities, inputs));
		}
	}
	return res;//!
}
std::vector<dp::TravelingSalesmanProblem::City> solveTSP(size_t cities, std::vector<std::vector<dp::TravelingSalesmanProblem::Distance>> const& inputs) {
	std::map<std::vector<dp::TravelingSalesmanProblem::City>, float> res;
	for (size_t i = 0; i < cities; i++)
		merge(res, solveTSP_inner({i}, 0.f, cities, inputs));

	dp::TravelingSalesmanProblem::Distance min = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::max();
	std::vector<dp::TravelingSalesmanProblem::City> output;
	for (auto it : res)
		if (it.second < min) {
			min = it.second;
			output = it.first;
		}
	return output;
}
std::vector<dp::TravelingSalesmanProblem::City> dp::TravelingSalesmanProblem::solve(std::vector<std::vector<Distance>> const& input_matrix) {
	return solveTSP(input_matrix.size(), input_matrix);
}