#pragma once
#include <functional>
namespace qs {
	template<typename Task>
	class AbstractStorage {
	public:
		virtual void push(Task *task = nullptr) abstract;
		virtual void repush(Task *task = nullptr) abstract;
		virtual Task pop() abstract;
		virtual Task pop_default(Task const& t) abstract;

		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) abstract;
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) abstract;

		virtual void clear() abstract;
		virtual size_t type() abstract;
	};
}