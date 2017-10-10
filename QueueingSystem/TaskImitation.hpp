#pragma once
using Time = float;
namespace qs {
	class QueueingSystemImitation;
	class TaskImitation {
		friend QueueingSystemImitation;

		Time generated;
		Time length;
		
		TaskImitation(Time generated, Time length = 0.f) : generated(generated), length(length) {}
	public:
		TaskImitation() : length(0.f) {}
	};
}