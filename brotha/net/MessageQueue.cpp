#include <algorithm>
#include "MessageQueue.cpp"


namespace net {

  void
  MessageQueue::push(Message* message) {
    Lock l__(this);
    mQueue.push_back(message);
  }


  void
  MessageQueue::read(std::vector<Message*> messages) {
    Lock l__(this);

    messages.clear();
    while (!mQueue.empty()) {
      messages.push_back(mQueue.front());
      mQueue.pop();
    }
  }

}
