#include "QueueingSystem.hpp"
#include "SimulatorUnit.hpp"
#include "LIFO.hpp"
#include "PER.hpp"
#include "EDF.hpp"

void qs::QueueingSystemSimulation::initialize(SystemType type) {
	switch (type) {
		case SystemType::LIFO:
			m_storage = new LIFO<TaskSimulation>();
			break;
		case SystemType::PER:
			m_storage = new PER<TaskSimulation>();
			break;
		case SystemType::EDF:
			m_storage = new EDF<TaskSimulation>();
			break;
		default:
			throw std::exception("Unsupported storage type was requested.");
	}

	m_generator = new GeneratorSimulator(m_storage, &m_time_coefficient, &m_state);
	m_processor = new ProcessorSimulator(m_storage, &m_time_coefficient, &m_state);
}

void qs::QueueingSystemImitation::initialize(SystemType type) {
	switch (type) {
		case SystemType::LIFO:
			m_storage = new LIFO<TaskImitation>();
			break;
		case SystemType::PER:
			m_storage = new PER<TaskImitation>();

			break;
		default:
			throw std::exception("Unsupported storage type was requested.");
	}
}