/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef THREAD_LOCK_H
#define THREAD_LOCK_H


#include "Lockable.h"


namespace thread {

   class Lock {
   public:
      Lock(Lockable* lockable) {
         mLockable = lockable;
         mLockable->lock();
      }

      ~Lock() {
         mLockable->unlock();
      }

   private:
      Lockable* mLockable;
   };

} // namespace thread


#endif // THREAD_LOCK_H
