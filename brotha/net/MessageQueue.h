#ifndef NET_MESSAGE_QUEUE_H
#define NET_MESSAGE_QUEUE_H


#include <queue>
#include <vector>
#include "../thread/Lockable.h"
#include "Message.h"


namespace net {

  class MessageQueue : private thread::Synchronized {
  public:
    void push(Message* message);
    void read(std::vector<Message*> messages);

  private:
    std::queue<Message*> mQueue;
  };

}


#endif
