/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_MESSAGE_QUEUE_H
#define NET_MESSAGE_QUEUE_H


#include <queue>
#include <vector>
#include "../thread/Lockable.h"
#include "../thread/Synchronized.h"
#include "Message.h"


namespace net {

   class MessageQueue : private thread::Synchronized {
   public:
      void push(Message* message);
      void read(std::vector<Message*> &messages);

      /**
       * Gets the number of messages in this queue. This method is atomic.
       *
       * @return  the number of msgs in this queue
       */
      unsigned int getSize();

   private:
      std::queue<Message*> mQueue;
   };

} // namespace net


#endif // NET_MESSAGE_QUEUE_H
