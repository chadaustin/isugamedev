/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "ListenServer.h"

namespace server {
   ListenServer::ListenServer(std::vector<Client> *clients)
      : m_serverSocket(35791) {
         m_clients = clients;
   }

   ListenServer::~ListenServer() {
   }

   void ListenServer::run() {
      while(1) {
      }
   }
} // namespace server