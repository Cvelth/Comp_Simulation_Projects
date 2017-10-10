#include "QueueingSystem.hpp"
#include "TaskImitation.hpp"
#include <thread>
#include <random>

Time start_point = 0.f;
Time max = std::numeric_limits<Time>::max();

void qs::QueueingSystemImitation::run(size_t tasks) {
	std::thread t([tasks, this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::poisson_distribution<number> p(m_lambda);
		std::normal_distribution<number> n(m_mu, m_sigma);

		Time current_time = start_point;
		size_t tasks_generated = 0u;
		size_t tasks_processed = 0u;
		Time tasks_processing_time = 0u;
		Time next_generation = p(g);
		Time next_processing = m_tau;
		while (tasks_processed < tasks) {
			if (next_generation < next_processing) {
				current_time = next_generation;
				m_storage->push(new TaskImitation(current_time, n(g)));
				tasks_generated++;
				next_generation += p(g);
			} else {
				current_time = next_processing;
				try {
					auto task = m_storage->pop();
					if (task.length > m_tau) {
						task.length -= m_tau;
						m_storage->repush(&task);
					} else {
						tasks_processed++;
						tasks_processing_time += current_time - task.generated;
					}
				} catch (qs::Exceptions::EmptyQueue) {}
				next_processing += m_tau;
			}
		}
		auto average_processing_time = tasks_processing_time / tasks_processed;
		current_time = max;
	});
	t.detach();
}

//Git_hub_test