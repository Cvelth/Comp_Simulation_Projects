#pragma once
#include <list>
#include <vector>
#include <map>
#include <memory>
namespace pn {
	template <typename TaskType>
	class PetriNet {
	private:
		float m_tau;
		std::list<TaskType> m_awaiting;
		std::vector<std::shared_ptr<TaskType>> m_executing;
		std::map<PetriNet*, size_t> m_transitions;
	public:
		PetriNet(float tau, size_t cores = 1) : m_tau(tau) { m_executing.resize(cores); }
		void insert(TaskType const& task) {
			m_awaiting.push_back(task);
		}
		void tau() const { return m_tau; }
		void step(float &time) {
			for (size_t i = 0; i < Cores; i++)
				if (!m_awaiting.empty())
					if (!m_executing[i]) {
						m_executing[i] = m_awaiting.front();
						m_awaiting.pop_front();
					}
			time += m_tau;
		}
	};
}