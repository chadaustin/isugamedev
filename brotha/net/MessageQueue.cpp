/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include <algorithm>
#include "MessageQueue.h"
#include "../thread/Lock.h"

namespace net {

   void
   MessageQueue::push(Message* message) {
      thread::Lock l__(this);
      mQueue.push(message);
   }


   void
   MessageQueue::read(std::vector<Message*> &messages) {
      thread::Lock l__(this);

      messages.clear();
      while (!mQueue.empty()) {
         messages.push_back(mQueue.front());
         mQueue.pop();
      }
   }

} // namespace net
