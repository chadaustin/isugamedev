/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef CLIENT_H
#define CLIENT_H

#include "net/Socket.h"
#include "net/MessageQueue.h"
#include "ClientServer.h"

namespace server {
   class Client {
   public:
      Client(net::Socket *socket, net::MessageQueue *readQueue);
      ~Client();
   private:
      ClientServer *m_clientServer;
      net::Socket *m_socket;
   };
} // namespace server

#endif