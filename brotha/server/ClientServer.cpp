/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "ClientServer.h"

namespace server {
   ClientServer::ClientServer(net::MessageQueue *readQueue) {
      m_readQueue = readQueue;
   }

   ClientServer::~ClientServer() {
   }

   void ClientServer::run() {
      while(PR_AtomicIncrement(&mKillMe)) {
         PR_AtomicDecrement(&mKillMe);
      }
   }
} // namespace server
