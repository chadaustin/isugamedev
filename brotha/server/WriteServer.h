/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef WRITE_SERVER_H
#define WRITE_SERVER_H

#include "thread/Thread.h"
#include "net/MessageQueue.h"
#include "Client.h"
#include <vector>

namespace server {
   class WriteServer : public thread::Thread {
   public:
      WriteServer(std::vector<Client> *clients, net::MessageQueue *writeQueue);
      virtual ~WriteServer();

      virtual void run();
   private:
      std::vector<Client> *m_clients;
      net::MessageQueue *m_writeQueue;
   };
} // namespace server

#endif // WRITE_SERVER_H