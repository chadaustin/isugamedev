/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H

#include "thread/Thread.h"
#include "net/MessageQueue.h"

namespace server {
   class ClientServer : public thread::Thread {
   public:
      ClientServer(net::MessageQueue *readQueue);
      virtual ~ClientServer();

      virtual void run();
   private:
      net::MessageQueue *m_readQueue;
   };
} // namespace server

#endif // CLIENT_SERVER_H