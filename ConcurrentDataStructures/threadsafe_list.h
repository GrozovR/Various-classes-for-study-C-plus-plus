// threadsafe list
#pragma once

#include <memory>
#include <mutex>

namespace CDS {

template<typename T>
class threadsafe_list
{
public:
	threadsafe_list() = default;
	~threadsafe_list()
	{
		remove_if([](const node&){ return true; });
	}
	threadsafe_list(const threadsafe_list&) = delete;
	threadsafe_list& operator=(const threadsafe_list&) = delete;

	void push_front(const T& val)
	{
		std::unique_ptr<node> new_node(new node(val));
		std::lock_guard<std::mutex> lg(head.m);
		new_node->next = std::move(head.next);
		head.next = std::move(new_node);
	}

	template<typename Function>
	void for_each(Function f)
	{
		node* current = &head;
		std::unique_lock<std::mutex> lock(head.m);
		while(const node* next = current->next)
		{
			std::unique_lock<std::mutex> next_lock(next->m);
			lock.unlock();
			f(*next->data);
			current = next;
			lock = std::move(next_lock);
		}
	}

	template<typename Predicate>
	std::shared_ptr<T> find_first_if(Predicate p)
	{
		node* current = &head;
		std::unique_lock<std::mutex> lock(head.m);
		while (const node* next = current->next) {
			std::unique_lock<std::mutex> next_lock(next->m);
			lock.unlock();
			if (p(*next->data))
			{
				return next->data;
			}
			current = next;
			lock = std::move(next_lock);
		}
		return {};
	}

	template<typename Predicate>
	void remove_if(Predicate p)
	{
		node* current = &head;
		std::unique_lock<std::mutex> lock(head.m);
		while (const node* next = current->next) {
			std::unique_lock<std::mutex> next_lock(next->m);
			if (p(*next->data)) {
				std::unique_ptr<node> old_next = std::move(current->next); // Обязательно ли ?
				current->next = std::move(next->next);
				next_lock.unlock()
			} else {
				lock.unlock(); // TODO: обязательно ли нужно ли нам тут анлочить?
				current = next;
				lock = std::move(next_lock);
			}
		}
	}

private:
	struct node
	{
		std::mutex m;
		std::shared_ptr<T> data;
		std::unique_ptr<node> next;

		node() = default;
		node(const T& val)
			: data(std::make_shared<T>(val))
		{}
	};

	node head;
};
}