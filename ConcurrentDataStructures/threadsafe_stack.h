// Threadsafe stack using mutexes.
#pragma once
#include <mutex>
#include <memory>

namespace CDS {

struct empty_stack : std::exception
{
	const char* what() const throw();
};


template<typename T>
class threadsafe_stack
{
public:
	threadsafe_stack() {}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data;
	}
	threadsafe_stack& operator=(const threadsafe_stack& other) = delete;

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		std::shared_ptr<T> const res(
			std::make_shared<T>(std::move(data.top())));
		data.pop();
		return res;
	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		value = std::move(data.top());
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}

private:
	std::mutex m;
	std::stack<T> data;
};

} // namespace CDS
