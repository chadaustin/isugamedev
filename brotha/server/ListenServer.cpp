/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "ListenServer.h"

namespace server {
   ListenServer::ListenServer(net::NetMgr *netMgr)
      : m_serverSocket(35791) {
      m_netMgr = netMgr;
   }

   ListenServer::~ListenServer() {
   }

   void ListenServer::run() {
      while(PR_AtomicIncrement(&mKillMe)) {
         // accept new client connections, inform the NetMgr about them
         net::Socket *sock = m_serverSocket.accept();
         if(sock != NULL) {
            m_netMgr->handleSocket(sock);
         }

         PR_AtomicDecrement(&mKillMe);
      }
   }
} // namespace server