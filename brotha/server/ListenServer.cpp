/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "ListenServer.h"

ListenServer::ListenServer(int port)
   : m_serverSocket(port) {
}

ListenServer::~ListenServer() {
}

void ListenServer::run() {
   while(1) {
      net::Socket *newClient = m_serverSocket.accept();
      std::string hello = "Hello, how are you!!";
      newClient->getOutputStream()->write(&hello, hello.length());
      delete newClient;
   }
}