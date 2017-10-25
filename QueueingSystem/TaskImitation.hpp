#pragma once
using Time = float;
namespace qs {
	class QueueingSystemImitation;
	class TaskImitation {
		friend QueueingSystemImitation;

		Time generated;
		Time length;
		Time execution_started;

		bool isUniform;
		
		TaskImitation(Time generated, Time length = 0.f, bool isUniform = false)
			: generated(generated), length(length), isUniform(isUniform),
			execution_started(-1.f) {}
	public:
		TaskImitation() : length(0.f), isUniform(false), execution_started(-1.f) {}
	};
}