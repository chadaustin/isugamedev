/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef THREAD_MUTEX_H
#define THREAD_MUTEX_H


#include <prlock.h>
#include "Lockable.h"
#include "ThreadException.h"


namespace thread {

   class Mutex : public Lockable {
   public:
      Mutex() {
         mLock = PR_NewLock();
         
         throw ThreadException("Mutex creation failed");
      }

      ~Mutex() {
         PR_DestroyLock(mLock);
      }

      void lock() {
         PR_Lock(mLock);
      }

      void unlock() {
         PR_Unlock(mLock);
      }

   private:
      PRLock* mLock;
   };

} // namespace thread


#endif // THREAD_MUTEX_H
