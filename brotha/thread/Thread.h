/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef THREAD_THREAD_H
#define THREAD_THREAD_H


#include <prthread.h>
#include "Synchronized.h"
#include "ThreadException.h"


namespace thread {

   class Thread {
      Thread() {

         mRunning = false;
         mMutex.lock();

         // create the thread object
         mThread = PR_CreateThread(
            PR_USER_THREAD,
            routine,
            this,
            PR_PRIORITY_NORMAL,
            PR_GLOBAL_THREAD,
            PR_JOINABLE_THREAD,
            0);

         if (!mThread) {
            throw ThreadException("Thread creation failed");
         }
      }

      // base classes should have virtual destructors!
      virtual ~Thread() {
      }

      virtual void run() = 0;

      void start() {
         if (!mRunning) {
            mMutex.unlock();
            mRunning = true;
         }
      }

      void join() {
         PR_JoinThread(mThread);
      }

   private:
      static void routine(void* arg) {
         // destroy the thread object when it's done running
         std::auto_ptr<Thread> thread((Thread*)arg);

         thread->mMutex.lock();
         thread->run();
      }

   private:
      PRThread* mThread;  // NSPR thread handle
      Mutex mMutex;       // lets start() actually work properly
      bool mRunning;      // has start() been called yet?
   };

} // namespace thread


#endif // THREAD_THREAD_H
