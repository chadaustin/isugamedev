/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef WRITE_THREAD_H
#define WRITE_THREAD_H

#include "thread/Thread.h"
#include "MessageQueue.h"
#include "Socket.h"

namespace net {
   class WriteThread : public thread::Thread {
   public:
      WriteThread(Socket *socket, MessageQueue *writeQueue);
      virtual ~WriteThread();

      virtual void run();
   private:
      Socket *m_socket;
      MessageQueue *m_writeQueue;
   };
} // namespace net

#endif // WRITE_THREAD_H