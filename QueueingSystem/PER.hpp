#pragma once
#include "AbstractStorage.hpp"
#include <list>
#include "Task.hpp"
#include "shared.hpp"
#ifdef MULTI_THREADING
	#include <shared_mutex>
#endif

namespace qs {
	class PER : public AbstractStorage {
		#ifdef MULTI_THREADING
			std::shared_mutex m_mutex;
			std::shared_mutex m_repush_mutex;
		#endif
		std::list<Task> m_initial_queue;
		std::list<Task> m_repush_queue;
	public:
		PER() : m_initial_queue(), m_repush_queue() {}
		virtual void push(Task *task = nullptr) override {
			#ifdef MULTI_THREADING
				m_mutex.lock();
			#endif
			if (task)
				m_initial_queue.push_back(*task);
			else
				m_initial_queue.push_back(Task());
			#ifdef MULTI_THREADING
				m_mutex.unlock();
			#endif
		}
		virtual void repush(Task *task = nullptr) override {
			#ifdef MULTI_THREADING
				m_repush_mutex.lock();
			#endif
			if (task)
				m_repush_queue.push_back(*task);
			else
				m_repush_queue.push_back(Task());
			#ifdef MULTI_THREADING
				m_repush_mutex.unlock();
			#endif
		}
		virtual Task pop() override {
			Task ret;
			try {
				if (m_initial_queue.size()) {
					#ifdef MULTI_THREADING
						m_mutex.lock();
					#endif
					ret = m_initial_queue.front();
					m_initial_queue.pop_front();
					#ifdef MULTI_THREADING
						m_mutex.unlock();
					#endif
				} else if (m_repush_queue.size()) {
					#ifdef MULTI_THREADING
						m_repush_mutex.lock();
					#endif
					ret = m_repush_queue.front();
					m_repush_queue.pop_front();
					#ifdef MULTI_THREADING
						m_repush_mutex.unlock();
					#endif
				} else
					throw Exceptions::EmptyQueue();
			} catch (std::exception) {
				//Do nothing
			}
			return ret;
		}
		virtual Task pop_default(Task const& t) override {
			Task ret(t);
			try {
				if (m_initial_queue.size()) {
					#ifdef MULTI_THREADING
						m_mutex.lock();
					#endif
					ret = m_initial_queue.front();
					m_initial_queue.pop_front();
					#ifdef MULTI_THREADING
						m_mutex.unlock();
					#endif
				} else if (m_repush_queue.size()) {
					#ifdef MULTI_THREADING
						m_repush_mutex.lock();
					#endif
					ret = m_repush_queue.front();
					m_repush_queue.pop_front();
					#ifdef MULTI_THREADING
						m_repush_mutex.unlock();
					#endif
				}
			} catch (std::exception) {
				//Do nothing
			}
			return ret;
		}
		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) override {
			#ifdef MULTI_THREADING
				m_mutex.lock_shared();
			#endif
			try {
				for (auto t = m_initial_queue.rbegin(); t != m_initial_queue.rend(); t++)
					lambda(*t);
			} catch (std::exception) {
				//Do nothing
			}
			#ifdef MULTI_THREADING
				m_mutex.unlock_shared();
			#endif
		}
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) override {
			#ifdef MULTI_THREADING
				m_repush_mutex.lock_shared();
			#endif
			try {
				for (auto t = m_repush_queue.rbegin(); t != m_repush_queue.rend(); t++)
					lambda(*t);
			} catch (std::exception) {
				//Do nothing
			}
			#ifdef MULTI_THREADING
				m_repush_mutex.unlock_shared();
			#endif
		}
		virtual size_t type() override {
			return 2;
		}
	};
}