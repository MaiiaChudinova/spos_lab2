#include "pch.h"
#include "BakeryLock.h"
#include <algorithm>
#include <thread>

BakeryLock::BakeryLock()
{
}


BakeryLock::~BakeryLock()
{
}

void BakeryLock::lock(int id)
{
	entering[id] = true;
	int max = 0;
	for (int ticket : tickets)
	{
		max = std::max(max, ticket);
	}
	
	tickets[id] = max + 1;
	entering[id] = false;

	for (int i = 0; i < tickets.size(); ++i)
	{
		if (i != id)
		{
			while (entering[i]) { std::this_thread::yield(); } 
			while (tickets[i] != 0 && (tickets[id] > tickets[i] ||
				(tickets[id] == tickets[i] && i < id)))
			{
				std::this_thread::yield();
			}
		}
	}
	// The critical section goes here
}

void BakeryLock::unlock(int id)
{
	tickets[id] = 0;
}

int BakeryLock::get_max_number_of_threads()
{
	return MAX_NUM_THREADS;
}

int BakeryLock::get_id()
{
	return 0;
}

bool BakeryLock::register_thread()
{
	return false;
}

void BakeryLock::unregister_thread()
{
}

bool BakeryLock::reset(unsigned int new_max_id)
{
	return false;
}

bool BakeryLock::reset(unsigned int new_min_id, unsigned int new_max_id)
{
	return false;
}
