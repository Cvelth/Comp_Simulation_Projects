#pragma once
using Time = float;
namespace qs {
	class QueueingSystemImitation;
	class TaskImitation {
		friend QueueingSystemImitation;

		Time generated;

		TaskImitation(Time generated) : generated(generated) {}
	};
}