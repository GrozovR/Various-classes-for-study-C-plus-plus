#include "thread_pool.h"

namespace CDS {

thread_pool::thread_pool(size_t threads)
{
	for (size_t i = 0; i < threads; i++) {
		workers_.emplace_back([this]() {
			WorkerRoutine();
		});
	}
}

thread_pool::~thread_pool()
{
	// TODO

}

void thread_pool::Submit(Task task)
{
	queue_tasks_.Put(std::move(task));
}

void thread_pool::Wait()
{
	// TODO
}

void thread_pool::Stop()
{
	// TODO
}

void thread_pool::WorkerRoutine()
{
	while (true) {
		try {
			auto task = queue_tasks_.Take();
			task();
		} catch (std::exception& e) {
			// TODO:
		}		
	}
}

thread_pool_2::thread_pool_2()
	: done(false), joiner(threads)
{
	const unsigned thread_count = std::thread::hardware_concurrency();
	try {
		for( unsigned i = 0; i < thread_count; i++)
			threads.push_back(
				std::thread(&thread_pool_2::worker_thread, this));
	} catch (...) {
		done = true;
		throw;
	}
}

void thread_pool_2::worker_thread()
{
	while (!done) {
		std::function<void()> task;
		if(work_queue.try_pop(task))
			task();
		else
			std::this_thread::yield();
	}
}

} // CDS