/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Thread.h,v $
 * Date modified: $Date: 2002-04-28 16:41:07 $
 * Version:       $Revision: 1.16 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */

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
         Thread* thread = (Thread*)arg;

         thread->mMutex.lock();
         thread->run();
         thread->mRunning = false;
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
