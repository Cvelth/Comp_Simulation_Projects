#include "QueueingSystem.hpp"
#include "ImitatorUnit.hpp"
#include "SimulatorUnit.hpp"
#include "LIFO.hpp"
#include "PER.hpp"

void qs::QueueingSystemSimulation::initialize(SystemType type) {
	initializeStorage(type);
	m_generator = new GeneratorSimulator(m_storage, &m_time_coefficient, &m_state);
	m_processor = new ProcessorSimulator(m_storage, &m_time_coefficient, &m_state);
}

void qs::QueueingSystemImitation::initialize(SystemType type) {
	initializeStorage(type);
	m_generator = new GeneratorImitator(m_storage, &m_state);
	m_processor = new ProcessorImitator(m_storage, &m_state);
}

void qs::AbstractQueueingSystem::initializeStorage(SystemType type) {
	switch (type) {
		case SystemType::LIFO:
			m_storage = new LIFO();
			break;
		case SystemType::PER:
			m_storage = new PER();
			break;
		default:
			throw std::exception("Unsupported storage type was requested.");
	}
}

qs::SystemType qs::AbstractQueueingSystem::type() {
	auto t = m_storage->type();
	switch (t) {
		case 1:	return SystemType::LIFO;
		case 2:	return SystemType::PER;
		default: throw std::exception("Unsupported storage type was requested");
	}
}
