#include "mutex.h"

Mutex::Mutex(char *name) : m_mutex(NULL) {
   m_mutex = ::CreateMutex(NULL, false, name);
}

Mutex::~Mutex() {
   if(m_mutex != NULL) {
      unlock();
	   ::CloseHandle( m_mutex );
      m_mutex = NULL;
   }
}

bool Mutex::attemptLock() {
   return lock(0);
}

bool Mutex::lock(DWORD waitfor) {
   if(m_mutex == NULL)
      return false;
   return (WaitForSingleObject(m_mutex, waitfor) == WAIT_OBJECT_0);
}

void Mutex::unlock() {
   ReleaseMutex(m_mutex);
}