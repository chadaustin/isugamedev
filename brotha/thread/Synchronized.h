#ifndef THREAD_SYNCHRONIZED_H
#define THREAD_SYNCHRONIZED_H


#include <prlock.h>
#include "Lockable.h"


namespace thread {

  class Synchronized : public Lockable {
  public:
    Synchronized() {
      mLock = PR_NewLock();
      // XXXaegis - do we throw an exception if creating a lock fails?
    }

    ~Synchronized() {
      PR_DestroyLock(mLock);
    }

    virtual void lock() {
      PR_Lock(mLock);
    }

    virtual void unlock() {
      PR_Unlock(mLock);
    }
    
  private:
    PRLock* mLock;
  };

}


#endif
