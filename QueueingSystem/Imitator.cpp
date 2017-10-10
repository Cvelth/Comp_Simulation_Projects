#include "QueueingSystem.hpp"
#include <thread>
#include <random>

using Time = float;
Time start_point = 0.f;
Time max = std::numeric_limits<Time>::max();

struct Task {
	Time generated;
};

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
				
			} else {

			}
			tasks_processed++; //To get rid of.
		}
	});
	t.detach();
}