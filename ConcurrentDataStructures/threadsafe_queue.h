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

} // namespace CDS