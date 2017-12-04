#pragma once
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <random>
namespace pn {
	template <typename TaskType> class PetriNetSystemSimulator;	
	template <typename TaskType> class PetriNet {
		friend PetriNetSystemSimulator<TaskType>;
	private:
		std::string m_name;
		float m_tau;
		std::list<TaskType> m_awaiting;
		std::vector<std::tuple<bool, TaskType, size_t>> m_executing;
		std::map<PetriNet*, float> m_transitions;
		float m_weight_sum;
		size_t m_tacts;
		size_t m_queue_sum;
		std::mt19937_64 g;
		std::uniform_real_distribution<float> d;
	public:
		PetriNet(std::string name = ""s, float tau = 1.f, size_t cores = 1) 
			: m_tau(tau), m_name(name), m_weight_sum(0.f), m_queue_sum(0u),
			m_tacts(0), g(std::random_device()()) {

			m_executing.resize(cores); 
		}
		void insert(TaskType const& task) {
			m_awaiting.push_back(task);
		}
		void step(float &time) {
			m_queue_sum += m_awaiting.size();
			for (size_t i = 0; i < m_executing.size(); i++) {
				if (std::get<0>(m_executing[i])) {
					taskDone(std::get<1>(m_executing[i]));
					std::get<0>(m_executing[i]) = false;
				}
				if (!m_awaiting.empty())
					if (!std::get<0>(m_executing[i])) {
						std::get<0>(m_executing[i]) = true;
						std::get<1>(m_executing[i]) = m_awaiting.front();
						m_awaiting.pop_front();
						std::get<2>(m_executing[i])++;
					}
			}
			time += m_tau;
			m_tacts++;
		}
		void taskDone(TaskType &task) {
			if (m_transitions.empty()) 
				throw std::exception("There's nowhere to put executed task.");
			float r = d(g);
			auto it = m_transitions.begin();
			do {
				r -= it->second;
				it++;
			} while (r > 0.f);
			(--it)->first->insert(task);
		}
		void link(PetriNet *net, float value) { 
			m_transitions[net] = value;
			m_weight_sum += value;
			d = std::uniform_real_distribution<float>(0.f, m_weight_sum);
		}
		float weight(PetriNet const* other){
			for (auto& it : m_transitions)
				if (*it.first == *other)
					return it.second;
			return 0.f;
		}
		float operator[](PetriNet const* other) {
			return weight(other);
		}
		std::string name() const { return m_name; }
		float tau() const { return m_tau; }
		size_t cores() const { return m_executing.size(); }
		float usage(size_t core) const { 
			return float(std::get<2>(m_executing[core])) / m_tacts; 
		}
		std::vector<float> usage() const {
			std::vector<float> ret;
			for (auto it : m_executing)
				ret.push_back(float(std::get<2>(it)) / m_tacts);
			return ret;
		}
		void clear() {
			m_weight_sum = 0.f;
			m_queue_sum = 0u;
			m_tacts = 0u;
			m_awaiting.clear();
			for (auto &it : m_executing) {
				std::get<0>(it) = false;
				std::get<2>(it) = 0u;
			}
		}
		float queue() const { return float(m_queue_sum) / m_tacts; }
		std::map<PetriNet*, float> transitions() { return m_transitions; }
		std::map<PetriNet*, float> transitions() const { return m_transitions; }
		bool operator==(PetriNet const& other) {
			return m_name == other.m_name && m_tau == other.m_tau
				&& m_awaiting.size() == other.m_awaiting.size()
				&& m_executing.size() == other.m_executing.size()
				&& m_weight_sum == other.m_weight_sum;
		}
		void update(std::string name, size_t cores, float tau) {
			m_name = name;
			m_executing.resize(cores);
			m_tau = tau;
		}
		void update_link(pn::PetriNet<TaskType> *selected_link, float value) {
			if (value == 0.f)
				m_transitions.erase(selected_link);
			else
				m_transitions[selected_link] = value;
		}
	};
}