/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "WriteServer.h"

namespace server {
   WriteServer::WriteServer(std::vector<Client> *clients, net::MessageQueue *writeQueue) {
      m_clients = clients;
      m_writeQueue = writeQueue;
   }

   WriteServer::~WriteServer() {
   }

   void WriteServer::run() {
      while(1) {
      }
   }
} // namespace server
