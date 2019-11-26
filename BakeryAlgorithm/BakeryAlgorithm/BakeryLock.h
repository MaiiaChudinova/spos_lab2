#pragma once
#include "LockableConcepts.h"
#include "vector"

class BakeryLock :
	public thread_sync::FixnumLockable
{
public:
	BakeryLock();
	~BakeryLock();
	virtual int get_id()override;
	virtual bool register_thread()override;
	virtual void unregister_thread()override;
	virtual bool reset(unsigned int new_max_id)override;
	virtual bool reset(unsigned int new_min_id, unsigned int new_max_id)override;
	virtual void lock(int id)override;
	virtual void unlock(int id)override;
	virtual int get_max_number_of_threads()override;

private:

	const int MAX_NUM_THREADS = 100;
	std::vector<int> tickets = std::vector<int>(MAX_NUM_THREADS);
	std::vector<bool> entering = std::vector<bool>(MAX_NUM_THREADS);
};

