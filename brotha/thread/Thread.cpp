#include "Thread.h"

namespace thread {

Thread::Thread() {
}

Thread::~Thread() {
}

bool Thread::create() {
   m_thread = CreateThread(NULL,0, Thread::process, (LPVOID) this, 0, &m_id );

   if(m_thread == 0)
      return false;

   return true;
}

void Thread::release() {
   if(m_thread) {
      ::CloseHandle(m_thread);

      m_thread  = NULL;
      m_id = 0;
   }
}

DWORD WINAPI Thread::process(LPVOID parameter) {
   if (!parameter)
      return -1;

   Thread* thread = (Thread*)parameter;
   int ret = thread->run();

   ExitThread(-1);

   return ret;
}

long Thread::run() {
   return -1;
}

} // namespace thread