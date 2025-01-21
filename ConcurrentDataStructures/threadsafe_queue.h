// A thread-safe queue implementation using C++11 features.
// This queue allows multiple threads to safely push and pop elements concurrently.
// It provides methods to push elements, wait and pop elements, try to pop elements without waiting, and check if the queue is empty.
#pragma once
#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

namespace CDS {

template<typename T>
class threadsafe_queue
{
public:
	threadsafe_queue() {}

	void push(T new_value)
	{
		std::shared_ptr<T> new_data(
			std::make_shared<T>(std::move(new_value)));
		std::lock_guard<std::mutex> lock(m);
		data.push(new_data);
		data_cond.notify_one();
	}

	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lock(m);
		data_cond.wait(lock, [this] { return !data.empty(); });
		value = std::move(*data.front());
		data.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lock(m);
		data_cond.wait(lock, [this] { return !data.empty(); });
		std::shared_ptr<T> res = data.front();
		data.pop();
		return res;
	}

	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty())
			return false;
		value = std::move(*data.front());
		data.pop();
		return true;
	}

	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res = data.front();
		data.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}

private:
	mutable std::mutex m;
	std::queue<std::shared_ptr<T>> data;
	std::condition_variable data_cond;
};


template<typename T>
class queue
{
public:
	queue()
		: head(new node), tail(head.get())
	{}
	queue(const queue& other) = delete;
	queue& operator=(const queue& other) = delete;

	std::shared_ptr<T> try_pop()
	{
		std::unique_ptr<node> old_head = try_pop_head();
		return old_head ? old_head->data : std::shared_ptr<T>();
	}

	bool try_pop(T& value)
	{
		std::unique_ptr<node> old_head = try_pop_head(value);
		return old_head != nullptr;
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_ptr<node> old_head = wait_pop_head();
		return old_head->data;
	}

	void wait_and_pop(T& value)
	{
		std::unique_ptr<node> old_head = wait_pop_head(value);		
	}

	void push(T new_value)
	{
		std::shared_ptr<T> new_data(
			std::make_shared<T>(std::move(new_value)));
		std::unique_ptr<node> p(new node);
		{
			std::lock_guard<std::mutex> lg(tail_mutex);
			tail->data = new_data;
			const node* new_tail = p.get();
			tail->next = std::move(p);
			tail = new_tail;
		}
		data_cond.notify_one();
	}

	bool empty()
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);
		return head.get() != get_tail();
	}

private:
	struct node
	{
		std::shared_ptr<T> data;
		std::unique_ptr<node> next;
	};

	std::unique_ptr<node> head;
	node* tail;
	std::mutex tail_mutex;
	std::mutex head_mutex;
	std::condition_variable data_cond;

private:
	node* get_tail()
	{
		std::lock_guard<std::mutex> lg(tail_mutex);
		return tail;
	}

	std::unique_ptr<node> pop_head()
	{
		std::unique_ptr<node> old_head = std::move(head);
		head = std::move(old_head->next);
		return old_head;
	}

	std::unique_lock<std::mutex> wait_for_data()
	{
		std::unique_lock<std::mutex> head_lock(head_mutex);
		data_cond.wait(head_lock, [&]() { return head.get() != get_tail(); });
		return std::move(head_lock);
	}

	std::unique_ptr<node> wait_pop_head()
	{
		std::unique_lock<std::mutex> head_lock(wait_for_data());
		return pop_head();
	}

	std::unique_ptr<node> wait_pop_head(T& value)
	{
		std::unique_lock<std::mutex> head_lock(wait_for_data());
		value = std::move(*head->data);
		return pop_head();
	}

	std::unique_ptr<node> try_pop_head()
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);
		if (head.get() == get_tail())
			return std::unique_ptr<node>();
		return pop_head();
	}

	std::unique_ptr<node> try_pop_head(T& value)
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);
		if (head.get() == get_tail()) {
			return std::unique_ptr<node>();
		}
		value = std::move(*head->data);
		return pop_head();
	}
};
} // namespace CDS