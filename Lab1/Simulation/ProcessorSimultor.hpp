#pragma once
namespace cs {
	class TaskGenerator;
	class TaskStorage;
	class TaskProcessor;

	enum class StorageType {
		LIFO, PER
	};

	class ProcessorSimulator {
		TaskGenerator* m_generator;
		TaskStorage* m_storage;
		TaskProcessor* m_processor;
	public:
		void initialize(StorageType type);
		void start();
		void pause();
		void stop();
	};
}