#pragma once
using Time = float;
namespace qs {
	class QueueingSystemImitation;
	class TaskImitation {
		friend QueueingSystemImitation;

		Time generated;
		Time length;
		Time execution_started;
		
		TaskImitation(Time generated, Time length = 0.f) 
			: generated(generated), length(length), 
			execution_started(-1.f) {}
	public:
		TaskImitation() : length(0.f) {}
	};
}