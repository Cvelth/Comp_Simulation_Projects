#pragma once
#include <vector>
namespace dp {
	namespace TravelingSalesmanProblem {
		using City = size_t;
		using Distance = float;
		/*
			Solves the Traveling Salesman Problem.
			It takes a matrix of all the distances as an input. 
			Matrix is represented as std::vector of std::vector of Distances.
			input_matrix[a][b] represents the distance from city with index 'a' to city with index 'b'.
			If there's no connection, it should be equal to 0.f.
			As a result, the function returns an array of cities: order in wich they would appear in the solution path,
			where result[0] is a first city to visit and result[number_of_cities - 1] -- last one.
		*/
		std::vector<City> solve(std::vector<std::vector<Distance>> const& input_matrix);
		namespace other_method {
			/*
			Solves the Traveling Salesman Problem.
			It takes a matrix of all the distances as an input.
			Matrix is represented as std::vector of std::vector of Distances.
			input_matrix[a][b] represents the distance from city with index 'a' to city with index 'b'.
			If there's no connection, it should be equal to 0.f.
			As a result, the function returns an array of cities: order in wich they would appear in the solution path,
			where result[0] is a first city to visit and result[number_of_cities - 1] -- last one.
			*/
			std::vector<City> solve(std::vector<std::vector<Distance>> const& input_matrix);
		}
	}
}