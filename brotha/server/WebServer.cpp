/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#include "WebServer.h"

namespace server {
   WebServer::WebServer()
      : m_serverSocket(8800) {
   }

   WebServer::~WebServer() {
   }

   void WebServer::run() {
      while(PR_AtomicIncrement(&mKillMe)) {
         // accept new client connections, inform the NetMgr about them
         net::Socket *sock = m_serverSocket.accept();
         if(sock != NULL) {
            processRequest(sock, readRequest(sock));
            delete sock;
         }

         PR_AtomicDecrement(&mKillMe);
      }
   }

   std::string WebServer::readRequest(net::Socket *socket) {
      std::string retVal;
      while(1) {
         char buffer[256];
         int bytesRead = socket->read(buffer, 256);
         retVal.resize(retVal.length() + bytesRead);
         std::copy(buffer, buffer+bytesRead, retVal.begin());
         if(retVal.find("\r\n\r\n") != std::string::npos) {
            break;
         }
         continue;
      }
      return retVal;
   }

   void WebServer::processRequest(net::Socket *socket, std::string &str) {
      /// @todo actually process request and generate dynamic response :)

      std::string response = "HTTP/1.0 200\r\nDate: Thu, 28 Mar 2002 12:54:45 GMT\r\nServer: \
                              Warn-A-Brotha Web Server\r\nContent-Length: 46\r\nContent-Type: \
                              text/html\r\n\r\n<HTML><FONT size=7><CENTER>No!!!</CENTER></FONT>\
                              </HTML>";
      sendResponse(socket, response);
   }

   void WebServer::sendResponse(net::Socket *socket, std::string &str) {
      int written = 0;
      int toWrite = (int)str.length();
      char buffer[64];
      while(toWrite > 0) {
         using namespace std;
         int write = min(toWrite, 64);
         std::copy(str.begin() + written, str.begin() + written + write, buffer);
         socket->write(buffer, write);
         written += write;
         toWrite -= write;
      }
   }
} // namespace server
