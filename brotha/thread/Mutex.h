#pragma once

#include <windows.h>

class Mutex {
public:
   Mutex(char *name = 0);
	virtual ~Mutex();

	bool attemptLock();
	bool lock(DWORD waitfor = INFINITE);
	void unlock();
private:
   HANDLE m_mutex;
};
