#ifndef THREAD_MUTEX_H
#define THREAD_MUTEX_H


#include <prlock.h>
#include "Lockable.h"


namespace thread {

  class Mutex : public Lockable {
  public:
    Mutex() {
      mLock = PR_NewLock();
      // XXXaegis throw an exception if this fails?
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

}


#endif
