#pragma once
#include "PetriNet.hpp"
#include <numeric>
namespace pn {
	template <typename TaskType> class PetriNetSystemSimulator {
	protected:
		static size_t next_step(std::vector<float> time) {
			float min = std::numeric_limits<float>::max();
			size_t res = -1;
			for (size_t i = 0; i < time.size(); i++)
				if (time[i] < min) {
					min = time[i];
					res = i;
				}
			return res;
		}
	public:
		static float simulate(std::vector<std::shared_ptr<PetriNet<TaskType>>> nets, std::vector<TaskType> tasks, size_t total_tasks) {
			auto start_tasks = total_tasks;
			for (auto &it : nets)
				it->clear();
			std::vector<float> time;
			for (auto it : tasks)
				nets.front()->insert(it);
			time.resize(nets.size());
			for (size_t i = 0; i < nets.size(); i++)
				nets[i]->step(time[i]);
			size_t state = 0u;
			while (total_tasks) {
				size_t i = next_step(time);
				nets[i]->step(time[i]);
				total_tasks--;
				bool is_stated = true;
				for (auto it : nets) 
					if (it->awaiting() != 4 && it->awaiting() != 0)
						is_stated = false;
				if (is_stated)
					state++;
			}
			return float(state) / start_tasks;
		}
	};
}