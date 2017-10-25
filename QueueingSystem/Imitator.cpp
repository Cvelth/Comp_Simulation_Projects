#include "QueueingSystem.hpp"
#include "TaskImitation.hpp"
#include <thread>
#include <random>
#include "Statistics.hpp"

Time const start_point = 0.f;
Time const max = std::numeric_limits<Time>::max();

void qs::QueueingSystemImitation::run(size_t tasks, ImitationStatistics *stats, UniformStatistics *uniform_stats, bool detach) {
	std::thread t([tasks, stats, uniform_stats, this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::poisson_distribution<number> p(1.f / m_lambda);
		std::normal_distribution<number> n(1.f / m_mu, m_sigma);
		if (stats) stats->clear();
		if (uniform_stats) uniform_stats->clear();
		m_storage->clear();
		Time current_time = start_point;
		size_t tasks_generated = 0u;
		size_t tasks_processed = 0u;
		qs::number t = p(g);
		Time next_generation = (t <= 0.f ? 0.f : 1.f / t);
		Time next_processing = m_tau;
		while (tasks_processed < tasks) {
			if (next_generation < next_processing) {
				t = n(g);
				if (uniform_stats && tasks_generated % uniform_stats->frequency() == 0)
					m_storage->push(new TaskImitation(next_generation, uniform_stats->duration(), true));
				else
					m_storage->push(new TaskImitation(next_generation, t <= 0 ? 0.f : t));
				tasks_generated++;
				current_time = next_generation;
				t = p(g);
				next_generation += (t <= 0.f ? 0.f : 1.f / t);
			}
			else {
				try {
					auto task = m_storage->pop();
					if (task.execution_started < 0.f)
						task.execution_started = current_time;
					if (task.length > m_tau) {
						task.length -= m_tau;
						m_storage->repush(&task);
					}
					else {
						tasks_processed++;
						if (uniform_stats && task.isUniform)
							uniform_stats->add_task(task.execution_started - task.generated,
								next_processing - task.generated);
						stats->add_task(task.execution_started - task.generated,
							next_processing - task.generated);
					}
				}
				catch (qs::Exceptions::EmptyQueue) {}
				current_time = next_processing;
				next_processing += m_tau;
			}
		}
		stats->task_execution_percentage(float(tasks) / tasks_generated);
		if (uniform_stats)
			uniform_stats->task_execution_percentage(float(uniform_stats->tasks_number())
				/ tasks_generated * uniform_stats->frequency());
	});
	if (detach)
		t.detach();
	else
		t.join();
}