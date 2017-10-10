#pragma once
#include "AbstractStorage.hpp"
#include <vector>
#include "shared.hpp"
#ifdef MULTI_THREADING
	#include <shared_mutex>
#endif

namespace qs {
	template<typename Task>
	class LIFO : public AbstractStorage<Task> {
		#ifdef MULTI_THREADING
			std::shared_mutex m_mutex;
		#endif
		std::vector<Task> m_queue;
	public:
		LIFO() : m_queue() {}
		virtual void push(Task *task = nullptr) override {
			#ifdef MULTI_THREADING
				m_mutex.lock();
			#endif
			if (task)
				m_queue.push_back(*task);
			else
				m_queue.push_back(Task());
			#ifdef MULTI_THREADING
				m_mutex.unlock();
			#endif
		}
		virtual void repush(Task *task = nullptr) override {
			push(task);
		}
		virtual Task pop() override {
			Task ret;
			if (m_queue.size()) {
				#ifdef MULTI_THREADING
					m_mutex.lock();
				#endif
				ret = m_queue.back();
				m_queue.pop_back();
				#ifdef MULTI_THREADING
					m_mutex.unlock();
				#endif
			} else {
				throw Exceptions::EmptyQueue();
			}
			return ret;
		}
		virtual Task pop_default(Task const& t) override {
			Task ret(t);
			if (m_queue.size()) {
				#ifdef MULTI_THREADING
					m_mutex.lock();
				#endif
				ret = m_queue.back();
				m_queue.pop_back();
				#ifdef MULTI_THREADING
					m_mutex.unlock();
				#endif
			}
			return ret;
		}
		virtual void for_each_push(std::function<void(Task const& task)> const& lambda) override {
			#ifdef MULTI_THREADING
				m_mutex.lock_shared();
			#endif
			for (auto t = m_queue.rbegin(); t != m_queue.rend(); t++)
				lambda(*t);
			#ifdef MULTI_THREADING
				m_mutex.unlock_shared();
			#endif
		}
		virtual void for_each_repush(std::function<void(Task const& task)> const& lambda) override {
			return for_each_push(lambda);
		}
		virtual size_t type() override {
			return 1;
		}
	};
}