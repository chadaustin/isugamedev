/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef LISTEN_SERVER_H
#define LISTEN_SERVER_H

#include "thread/Thread.h"
#include "net/ServerSocket.h"

class ListenServer : public thread::Thread {
public:
   ListenServer(int port);
   virtual ~ListenServer();

   virtual void run();
private:
   net::ServerSocket m_serverSocket;
};

#endif