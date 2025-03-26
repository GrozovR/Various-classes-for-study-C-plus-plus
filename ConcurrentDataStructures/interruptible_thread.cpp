#include "interruptible_thread.h"

namespace CDS {

void interrupt_flag::set()
{
	flag.store(true, std::memory_order_relaxed);
	std::lock_guard lk(set_clear_mutex);
	if (thread_cond)
		thread_cond->notify_all();
}

bool interrupt_flag::is_set() const
{
	return flag.load(std::memory_order_relaxed);
}

void interrupt_flag::set_cond_var(std::condition_variable& cv)
{
	std::lock_guard lk(set_clear_mutex);
	thread_cond = &cv;
}

void interrupt_flag::clear_cond_var()
{
	std::lock_guard lk(set_clear_mutex);
	thread_cond = nullptr;
}

class thread_interrupted : public std::exception
{
	// TODO:
};

void interruption_point()
{
	if( this_thread_interrupt_flag.is_set())
		throw thread_interrupted();
}

void interruptible_wait(std::condition_variable& cv,
	std::unique_lock<std::mutex>& lk)
{
	interruption_point();
	this_thread_interrupt_flag.set_cond_var(cv);
	interrupt_flag::clear_cv_on_destruct guard;
	interruption_point();
	cv.wait_for(lk, std::chrono::milliseconds(1));
	interruption_point();
}

}
