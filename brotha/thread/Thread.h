#pragma once

#include <windows.h>

class Thread
{
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
