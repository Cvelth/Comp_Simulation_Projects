#pragma once
#include "Shared.hpp"
#include <deque>
#include <mutex>

namespace cs {
	namespace Exceptions {
		class EmptyQueue {};
	}
	class Task {

	public:
		Task& operator=(Task const &other) {
			return *this;
		}
	};
	class Queue : public std::deque<Task> {};
	class TaskStorage {
	protected:
		std::mutex m_mutex;
	public:
		virtual void push(Task *task = nullptr) abstract;
		virtual void repush(Task *task = nullptr) abstract;
		virtual Task pop() abstract;
	};
	class LIFO : public TaskStorage {
		Queue m_queue;
	public:
		LIFO() : m_queue() {}
		virtual void push(Task *task = nullptr) override {
			std::lock_guard<std::mutex> l(m_mutex);
			if (task)
				m_queue.push_back(*task);
			else
				m_queue.push_back(Task());
		}
		virtual void repush(Task *task = nullptr) override {
			push(task);
		}
		virtual Task pop() override {
			Task ret;
			std::lock_guard<std::mutex> l(m_mutex);
			if (m_queue.size()) {
				ret = m_queue.back();
				m_queue.pop_back();
			} else
				throw Exceptions::EmptyQueue();
			return ret;
		}
	};
	/* To correct.
	class PER : public TaskStorage {
		Queue m_initial_queue;
		Queue m_repush_queue;
	public:
		PER() : m_initial_queue(), m_repush_queue() {}
		virtual void push(Task *task = nullptr) override {
			if (task)
				m_initial_queue.push_back(*task);
			else
				m_initial_queue.push_back(Task());
		}
		virtual void repush(Task *task = nullptr) override {
			if (task)
				m_repush_queue.push_back(*task);
			else
				m_repush_queue.push_back(Task());
		}
		virtual Task pop() override {
			Task ret;
			if (m_initial_queue.size())
				ret = m_initial_queue.front();
			else if (m_repush_queue.size())
				ret = m_repush_queue.front();
			else
				throw Exceptions::EmptyQueue();
			return ret; 
		}
	};
	*/
}