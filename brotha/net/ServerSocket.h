/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_SERVER_SOCKET_H
#define NET_SERVER_SOCKET_H


#include "Socket.h"


namespace net {

   class ServerSocket {
   public:
      ServerSocket(int port) {
         mSocket = PR_NewTCPSocket();
         if (!mSocket) {
            throw SocketException("Socket creation failed");
         }

         PRNetAddr addr;
         PRStatus status = PR_InitializeNetAddr(PR_IpAddrAny, port, &addr);
         if (status != PR_SUCCESS) {
            throw SocketException("Bind failed");
         }
      
         status = PR_Bind(mSocket, &addr);
         if (status != PR_SUCCESS) {
            throw SocketException("Bind failed");
         }

         status = PR_Listen(mSocket, 16);
         if (status != PR_SUCCESS) {
            throw SocketException("Listen failed");
         }
      }

      ~ServerSocket() {
         PRStatus status = PR_Close(mSocket);
         if( status != PR_SUCCESS) {
            throw SocketException("Close failed");
         }
      }

      Socket* accept() {
         PRNetAddr address;  // of connecting socket
         PRFileDesc* fd = PR_Accept(mSocket, &address, PR_INTERVAL_NO_TIMEOUT);
         return (fd ? new Socket(fd) : 0);
      }

   private:
      PRFileDesc* mSocket;
   };

}


#endif
