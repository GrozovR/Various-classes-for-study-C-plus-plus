#pragma once

#include <cassert>
#include <deque>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>
#include <condition_variable>

namespace CDS {

// Unbounded Multi-Producer / Multi-Consumer (MPMC) Blocking Queue
template<typename T>
class blocking_queue
{
public:
	// Thread role: producer
	void Put(T task)
	{
		std::lock_guard lock(mutex_);
		tasks_.emplace_back(std::move(task));
		not_empty_.notify_one();
	}

	// Thread role: consumer
	T Take()
	{
		std::unique_lock lock(mutex_);
		//cv_.wait(lock,[](){
			//return buffer_!.empty();});
		while (buffer_.empty()) {
			not_empty_.wait(lock);
		}
		return TakeLocked();
	}

private:
	std::condition_variable not_empty_;
	std::mutex mutex_;
	std::deque<T> buffer_;

	T TakeLocked()
	{
		assert(!buffer_.empty());
		T front{ std::move(buffer_.front()) };
		buffer_.pop_front();
		return front;
	}
};

using Task = std::function<void()>;

class thread_pool
{
public:
	explicit thread_pool(size_t threads);
	~thread_pool();

	thread_pool(const thread_pool&) = delete;
	thread_pool& operator=(const thread_pool&) = delete;

	// Schedules task for execution in one of the worker threads
	void Submit(Task task);

	// Waits until outstanding work count has reached zero
	void Wait();

	// Stops the worker threads as soon as posible
	// Pending tasks will be discarded
	void Stop();

private:
	blocking_queue<Task> queue_tasks_;
	std::vector<std::thread> workers_;

	void WorkerRoutine();
};

}