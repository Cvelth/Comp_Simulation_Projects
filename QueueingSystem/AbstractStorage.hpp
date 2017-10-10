#pragma once
namespace qs {
	class Task;
	template <typename StoredType = Task> class AbstractStorage {
	public:
		virtual void push(StoredType *task = nullptr) abstract;
		virtual void repush(StoredType *task = nullptr) abstract;
		virtual StoredType pop() abstract;
		virtual StoredType pop_default(StoredType const& t) abstract;

		virtual void for_each_push(std::function<void(StoredType const& task)> const& lambda) abstract;
		virtual void for_each_repush(std::function<void(StoredType const& task)> const& lambda) abstract;

		virtual size_t type() abstract;
	};
}