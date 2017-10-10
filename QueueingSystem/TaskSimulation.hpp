#pragma once
#include "shared.hpp"
namespace qs {
	class TaskSimulation {
		Color m_color;
		float m_processing_left;
		unsigned int m_was_processed;
	public:
		TaskSimulation(float color = -1.f, float processing_left = 0.f);
		TaskSimulation(TaskSimulation const &other) {
			m_color = other.m_color;
			m_processing_left = other.m_processing_left;
			m_was_processed = other.m_was_processed;
		}
		TaskSimulation& operator=(TaskSimulation const &other) {
			m_color = other.m_color;
			m_processing_left = other.m_processing_left;
			m_was_processed = other.m_was_processed;
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
	};
}