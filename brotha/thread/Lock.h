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
