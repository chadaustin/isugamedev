/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef READ_THREAD_H
#define READ_THREAD_H

#include "thread/Thread.h"
#include "MessageQueue.h"
#include "MessageReader.h"
#include "Socket.h"

namespace net {
   class ReadThread : public thread::Thread {
   public:
      ReadThread(Socket *socket, MessageQueue *readQueue);
      virtual ~ReadThread();

      virtual void run();
   private:
      Socket *m_socket;
      MessageQueue *m_readQueue;
   };
} // namespace net

#endif // READ_THREAD_H
