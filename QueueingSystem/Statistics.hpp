#pragma once
#include <vector>
namespace qs {
	class Statistics {
	protected:
		float m_lambda;
		float m_sigma;
		float m_mu;
		float m_tau;
	public:
		Statistics(float lambda = 0.f, float sigma = 0.f, float mu = 0.f, float tau = 0.f) 
			: m_lambda(lambda), m_sigma(sigma), m_mu(mu), m_tau(tau) {};
		~Statistics() {}

		inline float lambda() const { return m_lambda; }
		inline float sigma() const { return m_sigma; }
		inline float mu() const { return m_mu; }
		inline float tau() const { return m_tau; }

		virtual void clear() abstract;
		virtual void recheck() abstract;
	};

	class ImitationStatistics : public Statistics {
	protected:
		struct TaskStatistics {
			float waiting_time;
			float full_time;
		};
		std::vector<TaskStatistics> m_tasks;
		float m_task_execution_percentage;
		float m_average_time;
	protected:
		inline float urgency(float t, float t1, float t2) {
			if (t <= t1)
				return 1.f;
			else if (t <= t2)
				return 1.f - (t - t1) / (t2 - t1);
			else
				return 0.f;
		}
	public:
		ImitationStatistics(float lambda = 0.f, float mu = 0.f, float tau = 0.f) 
			: Statistics(lambda, mu, tau), m_task_execution_percentage(-1.f), m_average_time(-1.f) {}

		virtual void recheck() override {
			m_task_execution_percentage = -1.f;
			m_average_time = -1.f;
		}
		virtual void clear() override {
			m_tasks.clear();
			recheck();
		}

		inline void task_execution_percentage(float value) {
			m_task_execution_percentage = value;
		}
		inline float task_execution_percentage() const {
			return m_task_execution_percentage;
		}
		inline void add_task(float time_waited, float full_time) {
			m_tasks.push_back({ time_waited, full_time });
			recheck();
		}
		inline float average_time() {
			if (m_average_time < 0.f) {
				float sum = 0.f;
				for (auto it : m_tasks)
					sum += it.full_time;
				return m_average_time = (sum / m_tasks.size());
			}
			else
				return m_average_time;
		}
		inline float time_dispersion() {
			average_time();
			float sum = 0.f;
			for (auto it : m_tasks) {
				auto temp = m_average_time - it.full_time;
				sum += temp * temp;
			}
			return sum / m_tasks.size();
		}
		inline float average_waiting() {
			float sum = 0.f;
			for (auto it : m_tasks)
				sum += it.waiting_time;
			return sum / m_tasks.size();
		}
		inline float urgency(float t1, float t2) {
			float sum = 0.f;
			for (auto it : m_tasks)
				sum += urgency(it.full_time, t1, t2);
			return sum / m_tasks.size();
		}
		inline size_t tasks_number() const {
			return m_tasks.size();
		}
	};

	class UniformStatistics : public ImitationStatistics {
		float m_duration;
		size_t m_frequency;
	public:
		UniformStatistics(float duration, size_t frequency,
			float lambda = 0.f, float mu = 0.f, float tau = 0.f)
			: ImitationStatistics(lambda, mu, tau), 
			m_duration(duration), m_frequency(frequency) {}

		inline float duration() const { return m_duration; }
		inline size_t frequency() const { return m_frequency; }
	};
}