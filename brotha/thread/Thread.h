/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef THREAD_THREAD_H
#define THREAD_THREAD_H


#include <memory>
#include <prthread.h>
#include <pratom.h>
#include "Synchronized.h"
#include "ThreadException.h"


namespace thread {

   class Thread {
   public:
      Thread() {

         PR_AtomicSet(&mKillMe, 0);
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

      void stop() {
         if(mRunning) {
            PR_AtomicDecrement(&mKillMe);
            PR_Interrupt(mThread); // forces all blocked calls to die
            join();
            mRunning = false;
         }
      }

      /**
       * Tests if the thread is currently executing in its run loop.
       *
       * @return  true if the thread is alive; false otherwise
       */
      bool isRunning() {
         return mRunning;
      }

      void join() {
         PR_JoinThread(mThread);
      }

   private:
      static void PR_CALLBACK routine(void* arg) {
         // destroy the thread object when it's done running
         std::auto_ptr<Thread> thread((Thread*)arg);

         thread->mMutex.lock();
         thread->run();
      }

   private:
      PRThread* mThread;  // NSPR thread handle
      Mutex mMutex;       // lets start() actually work properly
      bool mRunning;      // has start() been called yet?
   protected:
      PRInt32 mKillMe;    // used for clean termination
   };

} // namespace thread


#endif // THREAD_THREAD_H
