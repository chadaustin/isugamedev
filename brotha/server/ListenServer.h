/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef LISTEN_SERVER_H
#define LISTEN_SERVER_H

#include "thread/Thread.h"
#include "net/ServerSocket.h"
#include "net/NetMgr.h"

namespace server {
   class ListenServer : public thread::Thread {
   public:
      ListenServer(net::NetMgr *netMgr);
      virtual ~ListenServer();

      virtual void run();
   private:
      net::ServerSocket m_serverSocket;
      net::NetMgr *m_netMgr;
   };
} // namespace server

#endif // LISTEN_SERVER_H