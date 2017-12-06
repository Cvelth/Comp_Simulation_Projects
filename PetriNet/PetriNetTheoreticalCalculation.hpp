#pragma once
#include "PetriNet.hpp"
namespace pn {
	template <typename TaskType> class PetriNetTheoreticalCalculation {

	public:
		static std::vector<std::pair<std::string, float>> calculate(std::vector<std::shared_ptr<PetriNet<TaskType>>> nets, std::vector<TaskType> tasks) {
			std::vector<std::pair<std::string, float>> ret;
			for (auto &it : nets) {
				it->clear();
				ret.push_back(std::make_pair(it->name(), 0.f));
			}
			for (auto it : tasks)
				nets.front()->insert(it);

			//Calculations are to be inserted here.

			return ret;
		}
	};
}