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
} // CDS