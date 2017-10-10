#pragma once
#include "ExecutionUnit.hpp" 
namespace qs {
	class ImitatorUnit : public ExecutionUnit {
	public:
		using ExecutionUnit::ExecutionUnit;
	};

	class GeneratorImitator : public ImitatorUnit, public GeneratorUnit {
	protected:
		virtual void loop() override;
	public:
		using ImitatorUnit::ImitatorUnit;
		virtual float getCurrentPercent() override;

		virtual bool is_running() override {
			return *m_state == SystemState::Running;
		}
		virtual void start() override { ImitatorUnit::start(); }
		virtual void pause() override { ImitatorUnit::pause(); }
		virtual void stop() override { ImitatorUnit::stop(); }
		virtual qs::Color const getCurrentColor() override { return ImitatorUnit::getCurrentColor(); }
	};
	class ProcessorImitator : public ImitatorUnit, public ProcessorUnit {
	protected:
		virtual void loop() override;
	public:
		using ImitatorUnit::ImitatorUnit;
		virtual float getCurrentPercent() override;

		virtual bool is_running() override {
			return *m_state == SystemState::Running;
		}
		virtual void start() override { ImitatorUnit::start(); }
		virtual void pause() override { ImitatorUnit::pause(); }
		virtual void stop() override { ImitatorUnit::stop(); }
		virtual qs::Color const getCurrentColor() override { return ImitatorUnit::getCurrentColor(); }
	};
}