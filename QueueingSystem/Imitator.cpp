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
		std::uniform_real_distribution<number> p(0.f, 1.f);
		std::normal_distribution<number> n(1.f / m_mu, 1.f / m_mu);
		if (stats) stats->clear();
		if (uniform_stats) uniform_stats->clear();
		m_storage->clear();
		Time current_time = start_point;
		size_t tasks_generated = 0u;
		size_t tasks_processed = 0u;

		qs::number *tasks_generation = new qs::number[tasks * 15];
		qs::number *tasks_processing = new qs::number[tasks * 15];
		for (size_t i = 0; i < tasks * 15; i++) {
			tasks_generation[i] = -1.f / m_lambda * log(p(g));
			do { tasks_processing[i] = n(g); } while (tasks_processing[i] <= 0);
		}
		Time next_generation = tasks_generation[tasks_generated];
		Time next_processing = m_tau;
		bool is_there_a_task = false;
		qs::TaskImitation task;
		while (tasks_processed < tasks) {
			if (next_generation < next_processing) {
				if (uniform_stats && tasks_generated % uniform_stats->frequency() == 0)
					m_storage->push(new TaskImitation(current_time, uniform_stats->duration(), true));
				else
					m_storage->push(new TaskImitation(current_time, tasks_processing[tasks_generated]));
				tasks_generated++;
				current_time = next_generation;
				next_generation += tasks_generation[tasks_generated];
			} else {
				if (is_there_a_task) {
					m_storage->repush(new qs::TaskImitation(task));
					is_there_a_task = false;
				}
				task = m_storage->pop_default(TaskImitation(-1));
				if (task.generated >= 0) {
					if (task.execution_started < 0.f)
						task.execution_started = current_time;
					if (task.length > m_tau) {
						task.length -= m_tau;
						is_there_a_task = true;s
					} else {
						tasks_processed++;
						if (uniform_stats && task.isUniform)
							uniform_stats->add_task(task.execution_started - task.generated,
								next_processing - task.generated);
						stats->add_task(task.execution_started - task.generated,
							current_time + task.length - task.generated);
					}
				}
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