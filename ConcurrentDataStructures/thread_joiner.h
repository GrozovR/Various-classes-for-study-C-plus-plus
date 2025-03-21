#pragma once

#include <vector>
#include <thread>

namespace CDS {

struct join_threads
{
	explicit join_threads(std::vector<std::thread>& _threads)
		: threads(_threads)
	{
	}

	~join_threads()
	{
		for (auto& thread : threads) {
			if (thread.joinable())
				thread.join();
		}
	}

	std::vector<std::thread>& threads;
};

}