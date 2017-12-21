#include "TravelingSalesmanProblem.hpp"
#include <map>
#include <algorithm>
#include <numeric>
#include <memory>
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
	return res;
}
std::vector<dp::TravelingSalesmanProblem::City> dp::TravelingSalesmanProblem::solve(std::vector<std::vector<Distance>> const& input_matrix) {
	std::map<std::vector<dp::TravelingSalesmanProblem::City>, float> res;
	merge(res, solveTSP_inner({0}, 0.f, input_matrix.size(), input_matrix));

	dp::TravelingSalesmanProblem::Distance min = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::max();
	std::vector<dp::TravelingSalesmanProblem::City> output;
	for (auto it : res)
		if (it.second < min) {
			min = it.second;
			output = it.first;
		}
	return output;
}
bool is_ignored(size_t i, size_t j, std::vector<std::pair<dp::TravelingSalesmanProblem::City, dp::TravelingSalesmanProblem::City>> ignored) {
	return i != j && std::find_if(ignored.begin(), ignored.end(), [&i, &j](std::pair<dp::TravelingSalesmanProblem::City, dp::TravelingSalesmanProblem::City> &it) { 
		return it.first == i || it.second == j || (it.first == j && it.second == i);
	}) == ignored.end();
}
std::vector<dp::TravelingSalesmanProblem::City> solveTSP_2(std::vector<std::vector<dp::TravelingSalesmanProblem::Distance>> const& input_matrix, 
														   std::vector<std::pair<dp::TravelingSalesmanProblem::City, dp::TravelingSalesmanProblem::City>> ignored = {}, 
														   std::shared_ptr<std::vector<dp::TravelingSalesmanProblem::City>> res = std::make_shared<std::vector<dp::TravelingSalesmanProblem::City>>())
{
	if (res->size() >= input_matrix.size())
		return *res;

	size_t size = input_matrix.size();
	std::vector<std::vector<dp::TravelingSalesmanProblem::Distance>> modified = input_matrix;
	for (size_t i = 0; i < size; i++) {
		dp::TravelingSalesmanProblem::Distance min = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::max();
		for (size_t j = 0; j < size; j++)
			if (is_ignored(i, j, ignored))
				if (modified[i][j] < min) {
					min = modified[i][j];
				}
		for (size_t j = 0; j < size; j++)
			if (is_ignored(i, j, ignored))
				modified[i][j] -= min;
	}

	for (size_t j = 0; j < size; j++) {
		dp::TravelingSalesmanProblem::Distance min = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::max();
		for (size_t i = 0; i < size; i++)
			if (is_ignored(i, j, ignored))
				if (modified[i][j] < min)
					min = modified[i][j];
		for (size_t i = 0; i < size; i++)
			if (is_ignored(i, j, ignored))
				modified[i][j] -= min;
	}

	dp::TravelingSalesmanProblem::Distance max_zero = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::min();
	size_t max_zero_i = 0u, max_zero_j = 0u;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			if (is_ignored(i, j, ignored))
				if (modified[i][j] == 0.f) {
					dp::TravelingSalesmanProblem::Distance min_x = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::max();
					dp::TravelingSalesmanProblem::Distance min_y = std::numeric_limits<dp::TravelingSalesmanProblem::Distance>::max();
					for (size_t k = 0; k < size; k++) 
						if (is_ignored(i, j, ignored)) {
							if (i != k && j != k && modified[i][k] < min_x)
								min_x = modified[i][k];
							if (i != k && j != k && modified[k][j] < min_y)
								min_y = modified[k][j];
					}
					if (min_x + min_y > max_zero) {
						max_zero = min_x + min_y;
						max_zero_i = i;
						max_zero_j = j;
					}
				}

	ignored.push_back(std::make_pair(max_zero_i, max_zero_j));
	if (!res->empty() && res->back() == max_zero_i) 
		res->push_back(max_zero_j);
	else {
		res->push_back(max_zero_i);
		res->push_back(max_zero_j);
	}
	return solveTSP_2(input_matrix, ignored, res);
}
std::vector<dp::TravelingSalesmanProblem::City> dp::TravelingSalesmanProblem::other_method::solve(std::vector<std::vector<Distance>> const& input_matrix) {
	return solveTSP_2(input_matrix);
}