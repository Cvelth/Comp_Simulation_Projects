#pragma once
#include "Shared.hpp"
#include <list>
#include <shared_mutex>
#include <functional>

namespace cs {
	namespace Exceptions {
		class EmptyQueue {};
	}
	class Task {
		Color m_color;
		float m_processing_left;
		unsigned int m_was_processed;
	public:
		Task(float color = -1.f, float processing_left = 0.f);
		Task(Task const &other) {
			m_color = other.m_color;
			m_processing_left = other.m_processing_left;
			m_was_processed = other.m_was_processed;
		}
		Task& operator=(Task const &other) {
			m_color = other.m_color;
			m_processing_left = other.m_processing_left;
			m_was_processed = other.m_was_processed;
			return *this;
		}
		inline Color const& color() const {
			return m_color;
		}
		inline float processing_left() const {
			return m_processing_left;
		}
		inline void set_processing_left(float value) {
			m_processing_left = value;
		}
		inline unsigned int was_processed() const {
			return m_was_processed;
		}
		inline void process() {
			m_was_processed++;
		}
	};
	class Queue : public std::list<Task> {};
	class TaskStorage {
	protected:
		std::shared_mutex m_mutex;
	public:
		virtual void push(Task *task = nullptr) abstract;
		virtual void repush(Task *task = nullptr) abstract;
		virtual Task pop() abstract;
		virtual Task pop_default(Task const& t) abstract;

		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) abstract;
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) abstract;

		virtual size_t type() abstract;
	};
	class LIFO : public TaskStorage {
		Queue m_queue;
	public:
		LIFO() : m_queue() {}
		virtual void push(Task *task = nullptr) override {
			m_mutex.lock();
			if (task)
				m_queue.push_back(*task);
			else
				m_queue.push_back(Task());
			m_mutex.unlock();
		}
		virtual void repush(Task *task = nullptr) override {
			push(task);
		}
		virtual Task pop() override {
			Task ret;
			if (m_queue.size()) {
				m_mutex.lock();
				ret = m_queue.back();
				m_queue.pop_back();
				m_mutex.unlock();
			} else {
				throw Exceptions::EmptyQueue();
			}
			return ret;
		}
		virtual Task pop_default(Task const& t) override {
			Task ret(t);
			if (m_queue.size()) {
				m_mutex.lock();
				ret = m_queue.back();
				m_queue.pop_back();
				m_mutex.unlock();
			}
			return ret;
		}
		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) override {
			m_mutex.lock_shared();
			for (auto t = m_queue.rbegin(); t != m_queue.rend(); t++)
				lambda(*t);
			m_mutex.unlock_shared();
		}
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) override {
			return for_each_push(lambda);
		}
		virtual size_t type() override {
			return 1;
		}
	};

	class PER : public TaskStorage {
		Queue m_initial_queue;
		Queue m_repush_queue;
		std::shared_mutex m_repush_mutex;
	public:
		PER() : m_initial_queue(), m_repush_queue() {}
		virtual void push(Task *task = nullptr) override {
			m_mutex.lock();
			if (task)
				m_initial_queue.push_back(*task);
			else
				m_initial_queue.push_back(Task());
			m_mutex.unlock();
		}
		virtual void repush(Task *task = nullptr) override {
			m_repush_mutex.lock();
			if (task)
				m_repush_queue.push_back(*task);
			else
				m_repush_queue.push_back(Task());
			m_repush_mutex.unlock();
		}
		virtual Task pop() override {
			Task ret;
			if (m_initial_queue.size()) {
				m_mutex.lock();
				ret = m_initial_queue.front();
				m_initial_queue.pop_front();
				m_mutex.unlock();
			} else if(m_repush_queue.size()) {
				m_repush_mutex.lock();
				ret = m_repush_queue.front();
				m_repush_queue.pop_front();
				m_repush_mutex.unlock();
			} else
				throw Exceptions::EmptyQueue();
			return ret;
		}
		virtual Task pop_default(Task const& t) override {
			Task ret(t);
			if (m_initial_queue.size()) {
				m_mutex.lock();
				ret = m_initial_queue.front();
				m_initial_queue.pop_front();
				m_mutex.unlock();
			} else if (m_repush_queue.size()) {
				m_repush_mutex.lock();
				ret = m_repush_queue.front();
				m_repush_queue.pop_front();
				m_repush_mutex.unlock();
			}
			return ret;
		}
		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) override {
			m_mutex.lock_shared();
			for (auto t = m_initial_queue.rbegin(); t != m_initial_queue.rend(); t++) 
				lambda(*t);
			m_mutex.unlock_shared();
		}
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) override {
			m_repush_mutex.lock_shared();
			for (auto t = m_repush_queue.rbegin(); t != m_repush_queue.rend(); t++)
				lambda(*t);
			m_repush_mutex.unlock_shared();
		}
		virtual size_t type() override {
			return 2;
		}
	};
}