#pragma once
#include "Shared.hpp"

namespace cs {
	class TaskStorage {			
	public:
		virtual void push() abstract;
		virtual bool pop() abstract;
		virtual void repush() abstract;
	};
	class LIFO : public TaskStorage {
		size_t m_queue;
	public:
		LIFO() : m_queue(0) {}
		virtual void push() override {
			m_queue++;
		}
		virtual bool pop() override {
			if (m_queue != 0) {
				m_queue--;
				return true;
			} else
				return false;
		}
		virtual void repush() override {
			push();
		}
	};
	class PER : public TaskStorage {
		size_t m_queue_1;
		size_t m_queue_2;
	public:
		PER() : m_queue_1(0), m_queue_2(0) {}
		virtual void push() override {
			m_queue_1++;
		}
		virtual bool pop() override {
			if (m_queue_1 != 0) {
				m_queue_1--;
				return true;
			} else if (m_queue_2 != 0) {
				m_queue_2--;
				return true;
			} else
				return false;
		}
		virtual void repush() override {
			m_queue_2++;
		}
	};
}