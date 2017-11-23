#pragma once
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
namespace pn {
	template <typename TaskType>
	class PetriNet {
	private:
		std::string m_name;
		float m_tau;
		std::list<TaskType> m_awaiting;
		std::vector<std::shared_ptr<TaskType>> m_executing;
		std::map<PetriNet*, float> m_transitions;
	public:
		PetriNet(std::string name = ""s, float tau = 1.f, size_t cores = 1) : m_tau(tau), m_name(name) { 
			m_executing.resize(cores); 
		}
		void insert(TaskType const& task) {
			m_awaiting.push_back(task);
		}
		void step(float &time) {
			for (size_t i = 0; i < m_executing.size(); i++)
				if (!m_awaiting.empty())
					if (!m_executing[i]) {
						m_executing[i] = m_awaiting.front();
						m_awaiting.pop_front();
					}
			time += m_tau;
		}
		void link(PetriNet *net, float value) { m_transitions[net] = value; }
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
		float usage() const { return 0.f; /*To implement*/ }
		std::map<PetriNet*, float> transitions() { return m_transitions; }
		std::map<PetriNet*, float> transitions() const { return m_transitions; }
		bool operator==(PetriNet const& other) {
			return m_name == other.m_name && m_tau == other.m_tau
				&& m_awaiting.size() == other.m_awaiting.size()
				&& m_executing.size() == other.m_executing.size();
		}
	};
}