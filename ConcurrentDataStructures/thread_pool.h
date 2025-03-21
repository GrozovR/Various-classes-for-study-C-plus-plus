#pragma once

#include <cassert>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <functional>
#include <future>
#include <thread>
#include <type_traits>
#include <vector>

#include "threadsafe_queue.h"
#include "thread_joiner.h"

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

class thread_pool_2
{
	thread_pool_2();
	~thread_pool_2() { done = true; }

	thread_pool_2(const thread_pool_2&) = delete;
	thread_pool_2& operator=(const thread_pool_2&) = delete;

	template<typename FunctionType>
	void submit(FunctionType f)
	{
		work_queue.push(std::function<void()>(f));
	}

private:
	// ѕор€док членов важен дл€ гарантии работы!
	// TODO: проверить, как уничтожаетс€ класс
	std::atomic_bool done;
	threadsafe_queue<std::function<void()>> work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;

	void worker_thread();
};


// --------------

class function_wrapper
{
	struct impl_base
	{
		virtual void call() = 0;
		virtual ~impl_base() {}
	};

	template<typename F>
	struct impl_type : impl_base
	{
		F f;
		impl_type(F&& f_) : f(std::move(f_)) {}
		void call() { f (); }
	};

public:
	function_wrapper() = default;

	template<typename F>
	function_wrapper(F&& f)
		: impl(new impl_type<F>(std::move(f)))
	{
	}
	
	function_wrapper(function_wrapper&& other) :
		impl(std::move(other.impl))
	{
	}
	function_wrapper& operator=(function_wrapper&& other)
	{
		impl = std::move(other.impl);
		return *this;
	}
	function_wrapper(const function_wrapper&) = delete;
	function_wrapper(function_wrapper&) = delete;
	function_wrapper& operator=(const function_wrapper&) = delete;


	void operator()() { impl->call(); }

private:
	std::unique_ptr<impl_base> impl;
};

class thread_pool_3
{
public:
	template<typename FuncType>
	auto submit(FuncType f) -> std::future<typename std::invoke_result<FuncType>::type>
	{
		using result_type = typename std::invoke_result<FuncType()>::type;
		std::packaged_task<result_type()> task(std::move(f));
		std::future<result_type> res( task.get_future());
		work_queue.push(std::move(task));
		return res;
	}

	void run_pending_task();

	// TODO: incompleted
	
private:
	std::atomic_bool done;
	threadsafe_queue<function_wrapper> work_queue;
	std::vector<std::thread> threads;
	join_threads joiner;
	
	void worker_thread();
};

}