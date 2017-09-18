#include "ProcessorSimultor.hpp"
#include "TaskGenerator.hpp"
#include "TaskProcessor.hpp"
#include "TaskStorage.hpp"

void cs::ProcessorSimulator::initialize(StorageType type) {
	switch (type) {
		case StorageType::LIFO:
			m_storage = new LIFO();
			break;
		case StorageType::PER:
			m_storage = new PER();
			break;
	}
	m_generator = new TaskGenerator(m_storage);
	m_processor = new TaskProcessor(m_storage);
}
