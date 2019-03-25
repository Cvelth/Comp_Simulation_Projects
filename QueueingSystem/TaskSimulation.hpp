#pragma once
#include "shared.hpp"
#include <chrono>
namespace qs {
	class TaskSimulation {
		Color m_color;
		float m_processing_left;
		unsigned int m_was_processed;
		std::chrono::high_resolution_clock::time_point m_creation_time;
		float m_expiration;
	public:
		TaskSimulation(float expiration = 0.f, float color = -1.f, float processing_left = 0.f);
		TaskSimulation(TaskSimulation const &other) {
			m_color = other.m_color;
			m_processing_left = other.m_processing_left;
			m_was_processed = other.m_was_processed;
			m_creation_time = other.m_creation_time;
			m_expiration = other.m_expiration;
		}
		TaskSimulation& operator=(TaskSimulation const &other) {
			m_color = other.m_color;
			m_processing_left = other.m_processing_left;
			m_was_processed = other.m_was_processed;
			m_creation_time = other.m_creation_time;
			m_expiration = other.m_expiration;
			return *this;
		}
		TaskSimulation& operator=(TaskSimulation &&other) {
			m_color = std::move(other.m_color);
			m_processing_left = std::move(other.m_processing_left);
			m_was_processed = std::move(other.m_was_processed);
			m_creation_time = std::move(other.m_creation_time);
			m_expiration = std::move(other.m_expiration);
			return *this;
		}
		inline Color const& color() const {
			return m_color;
		}
		inline float processing_left() const {
			return m_processing_left;
		}
		inline void set_processing_left(float value) {
			m_processing_left = value;
		}
		inline unsigned int was_processed() const {
			return m_was_processed;
		}
		inline void process() {
			m_was_processed++;
		}
		inline float expiration() const {
			return m_expiration;
		}
		inline void set_expiration_time(float value) {
			m_expiration = value;
		}
		bool is_expired() const;
	};
}