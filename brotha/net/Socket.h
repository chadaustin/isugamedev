/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_SOCKET_H
#define NET_SOCKET_H


#include <prio.h>
#include <prnetdb.h>
#include <string.h>
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "SocketException.h"


namespace net {

   class Socket {
   public:
      // XXXaegis this should probably be private
      Socket(PRFileDesc* fd) {
         mSocket = fd;
      }

      Socket(const char* hostname, int port) {
         mSocket = PR_NewTCPSocket();
         if (!mSocket) {
            throw SocketException("Socket creation failed");
         }

         PRNetAddr addr;
         memset(&addr, 0, sizeof(addr));

         PRStatus status = PR_StringToNetAddr(hostname, &addr);
         if (status != PR_SUCCESS) {
            throw SocketException("Hostname lookup failed");
         }

         addr.inet.family = PR_FamilyInet();
         addr.inet.port   = PR_htons(port);

         status = PRConnect(mSocket, &addr, PR_INTERVAL_NO_TIMEOUT);
         if (status != PR_SUCCESS) {
            throw SocketException("Connection failed");
         }
      }

      InputStream* getInputStream() {
         /// @todo implement getInputStream
         return 0;
      }

      OutputStream* getOutputStream() {
         /// @todo implement getOutputStream
         return 0;
      }

   private:
      PRFileDesc* mSocket;
   };

}


#endif
