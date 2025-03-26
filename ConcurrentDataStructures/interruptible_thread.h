#pragma once
#include <thread>
#include <future>

namespace CDS {

thread_local interrupt_flag this_thread_interrupt_flag;

class interrupt_flag
{
public:
	interrupt_flag() : thread_cond(nullptr) {}

	void set();
	bool is_set() const;
	void set_cond_var(std::condition_variable& cv);
	void clear_cond_var();

	struct clear_cv_on_destruct
	{
		~clear_cv_on_destruct()
		{
			this_thread_interrupt_flag.clear_cond_var();
		}
	};

private:
	std::atomic<bool> flag;
	std::condition_variable* thread_cond;
	std::mutex set_clear_mutex;
};

class interruptible_thread
{
public:
	template<typename FuncType>
	interruptible_thread(FuncType f)
	{
		std::promise<interrupt_flag*> p;
		internal_thread = std::thread([f, &p] {
			p.set_value(&this_thread_interrupt_flag);
			f();
			});
		flag = p.get_future().get();
	}

	void interrupt()
	{
		if (flag != nullptr)
			flag->set();
	}
private:
	std::thread internal_thread;
	interrupt_flag* flag;
};

void interruption_point();
void interruptible_wait(std::condition_variable& cv,
	std::unique_lock<std::mutex>& lk);

}