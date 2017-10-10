#include "QueueingSystem.hpp"
#include "TaskImitation.hpp"
#include <thread>
#include <random>

Time start_point = 0.f;
Time max = std::numeric_limits<Time>::max();

void qs::QueueingSystemImitation::run(size_t tasks) {
	std::thread t([&tasks, this]() {
		std::random_device seed;
		std::mt19937_64 g(seed());
		std::poisson_distribution<number> d(m_lambda);

		Time current_time = start_point;
		size_t tasks_generated = 0u;
		size_t tasks_processed = 0u;
		Time next_generation = (d)(g);
		Time next_processing = max;
		while (tasks_processed <= tasks) {
			if (next_generation < next_processing) {
				current_time = next_generation;
				m_storage->push(new TaskImitation(current_time));
			} else {

			}
			tasks_processed++; //To get rid of.
		}
	});
	t.detach();
}