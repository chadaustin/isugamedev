#if !defined(Mutex_H)
#define Mutex_H

#include <windows.h>

namespace thread {

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

} // namespace thread

#endif