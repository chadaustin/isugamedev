/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "thread/Thread.h"
#include "net/ServerSocket.h"
#include "net/NetMgr.h"
#include "net/InputStream.h"

namespace server {
   class WebServer : public thread::Thread {
   public:
      WebServer();
      virtual ~WebServer();

      virtual void run();

      std::string readRequest(net::Socket *socket);
      void processRequest(net::Socket *socket, std::string &str);
      void sendResponse(net::Socket *socket, std::string &str);
   private:
      net::ServerSocket m_serverSocket;
   };
} // namespace server

#endif // WEB_SERVER_H
