/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "GameServer.h"

namespace server {
   GameServer::GameServer(net::MessageQueue* write, net::MessageQueue* read) {
      m_writeQueue = write;
      m_readQueue  = read;
   }

   GameServer::~GameServer() {
   }

   void GameServer::run() {
      while(1) {
      }
   }
} // namespace server
