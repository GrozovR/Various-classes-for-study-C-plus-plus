#pragma once
#include <iterator>
#include <thread>
#include <vector>
#include <future>
#include "thread_pool.h"

namespace CDS {

template<typename Iterator, typename Func>
void parrallel_for_each(Iterator first, Iterator last, Func f)
{
	const unsigned long length = std::distance(first, last);
	if (length == 0)
		return;

	constexpr unsigned long min_per_thread = 25;
	constexpr unsigned long max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	constexpr unsigned long hardware_threads =
		std::thread::hardware_concurrency();

	constexpr unsigned long num_threads =
		std::min(hardware_threads != 0 hardware_threads:2, max_threads);

	constexpr unsigned long block_size = length / num_threads;

	std::vector<std::future<void>> futures(num_threads - 1);
	std::vector<std::thread> threads(num_threads - 1);

	join_threads joiner(threads);

	Iterator block_start = first;
	for (unsigned long i = 0; i < (num_threads - 1); ++i) {
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		std::packaged_task<void(void)> task(
			[]() {
				std::for_each(block_start, block_end, f);
			}
		);
		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task));
		block_start = block_end;
	}
	std::for_each(block_start, last, f);

	for (auto& future_ : futures)
		future_.get();
}

template<typename Iterator, typename Func>
void async_for_each(Iterator first, Iterator last, Func f)
{
	const unsigned long length = std::distance(first, last);
	if (length == 0)
		return;

	constexpr unsigned long min_per_thread = 25;
	if (length < 2 * min_per_thread)
		std::for_each(first, last, f);
	else {
		Iterator mid_point = first + length / 2;
		std::future<void> first_half =
			std::async(&async_for_each<Iterator, Func>,
				first, mid_point, f);
		parrallel_for_each(mid_point, last, f);
		first_half.get();
	}
}

template<typename Iterator, typename MatchType>
Iterator parrallel_find(Iterator first, Iterator last, MatchType match)
{
	struct find_element
	{
		void operator() (Iterator begin, Iterator end,
			MatchType match, std::promise<Iterator>* result,
			std::atomic<bool>* done_flag)
		{
			try {
				for (; (begin != end) && !done_flag->load(); ++begin) {
					if (*begin == match) {
						result->set_value(begin);
						done_flag->store(true);
						return;
					}
				}
			} catch (...) {
				try {
					result->set_exception(std::current_exception());
					done_flag->store(true);
				} catch (...) {
					// исключение может быть вызвано
					// в result->set_exception, если значение уже установлено
				}
			}
		}
	};

	const unsigned long length = std::distance(first, last);
	if (length == 0)
		return last;

	// TODO: это общее для всех
	constexpr unsigned long min_per_thread = 25;
	constexpr unsigned long max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	constexpr unsigned long hardware_threads =
		std::thread::hardware_concurrency();

	constexpr unsigned long num_threads =
		std::min(hardware_threads != 0 hardware_threads:2, max_threads);

	constexpr unsigned long block_size = length / num_threads;
	// --------------

	std::promise<Iterator> result;
	std::atomic<bool> done_flag(false);
	std::vector<std::thread> threads(num_threads -1);
	{
		join_threads joiner(threads);
		Iterator block_start = first;
		for (unsigned long i = 0; i < (num_threads - 1); ++i) {
			Iterator block_end = block_start;
			std::advance(block_end, block_size);
			threads[i] = std::thread(find_element(),
				block_start, block_end, match, &result, &done_flag);
		
			block_start = block_end;
		}
		find_element()(block_start, last, match, & result, & done_flag);
	}

	if (!done_flag.load()) {
		// разрушение join_thread гарантирует завершение потоков
		return false;
	}
	return result.get_future().get();
}

// -----

template<typename T>
struct sorter
{
	std::list<T> do_sort(std::list<T>& chunk_data)
	{
		if(chink_data.empty())
			return chunk_data;

		std::list<T> result;
		result.splice(result.begin(), chunk_data, chunk_data.begin());
		const T& partition_val = *result.begin();

		typename std::list<T>::iterator divide_point =
			std::partition(chunk_data.begin(), chunk_data.end(),
				[&](const T& val) { return val < partition_val; } );
		std::list<T> new_lower_chunk;
		new_lower_chunk.splice(new_lower_chunk.end(),
			chunk_data, chunk_data.begin(), divide_point);

		std::future<std::list<T>> new_lower =
			pool.submit(std::bind(&sorter::do_sort, this,
				std::move(new_lower_chunk)));

		std::list<T> new_higher(do_sort(chunk_data));

		result.splice(result.end(),new_higher);
		while(!new_lower.wait_for(std::chrono::seconds(0))
			== std::future::timeout)
		{
			pool.run_pending_task();
		}
		result.splice(result.begin(), new_lower.get());
		return result;
	}
	thread_pool_3 pool;
};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
	if(input.empty())
		return input;

	sorter<T> s;
	return s.do_sort(input);
}

}
