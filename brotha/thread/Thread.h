#if !defined(Thread_H)
#define Thread_H

#include <windows.h>

namespace thread {

class Thread {
public:
   Thread();
   virtual ~Thread();

   bool create();
   void release();

   virtual long run();

   static DWORD WINAPI process(LPVOID parameter);
private:
   HANDLE m_thread;
   DWORD m_id;
};

} // namespace thread

#endif