#include "ProcessorSimulator.hpp"
#include "TaskGenerator.hpp"
#include "TaskProcessor.hpp"
#include "TaskStorage.hpp"

cs::ProcessorSimulator::ProcessorSimulator() : m_state(cs::SimulationState::Stoped) {}

void cs::ProcessorSimulator::initialize(StorageType type) {
	switch (type) {
		case StorageType::LIFO:
			m_storage = new LIFO();
			break;
		case StorageType::PER:
			m_storage = new PER();
			break;
	}
	m_generator = new TaskGenerator(m_storage, &m_time_coefficient, &m_state);
	m_processor = new TaskProcessor(m_storage, &m_time_coefficient, &m_state);
}

void cs::ProcessorSimulator::start() {
	m_generator->start();
	m_processor->start();
}
void cs::ProcessorSimulator::pause() {
	m_generator->pause();
	m_processor->pause();
}
void cs::ProcessorSimulator::stop() {
	m_generator->stop();
	m_processor->stop();
}

void cs::ProcessorSimulator::changeTimeCoefficient(number c) {
	m_time_coefficient = c;
}

void cs::ProcessorSimulator::changeLambda(number l) {
	m_generator->changeLambda(l);
}

void cs::ProcessorSimulator::changeMu(number m) {
	m_processor->changeMu(m);
}

void cs::ProcessorSimulator::changeSigma(number s) {
	m_processor->changeSigma(s);
}

void cs::ProcessorSimulator::changeTau(number t) {
	m_processor->changeTau(t);
}

bool cs::ProcessorSimulator::is_running() {
	return m_generator->is_running() && m_processor->is_running();
}
cs::StorageType cs::ProcessorSimulator::type() {
	auto t = m_storage->type();
	switch (t) {
		case 1:	return StorageType::LIFO;
		case 2:	return StorageType::PER;
	}
}