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
         mOutputStream = 0;
         mSocket = fd;
      }

      ~Socket() {
         if(mOutputStream == 0) {
            delete mOutputStream;
         }
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
         if(mInputStream == 0) {
            mInputStream = new SocketInputStream(this);
         }
         return mInputStream;
      }

      OutputStream* getOutputStream() {
         if(mOutputStream == 0) {
            mOutputStream = new SocketOutputStream(this);
         }
         return mOutputStream;
      }

      void read(void* buffer, int size) {
         PR_Recv(mSocket, buffer, size, 0, PR_INTERVAL_NO_TIMEOUT);
      }

      void write(void* buffer, int size) {
         PR_Send(mSocket, buffer, size, 0, PR_INTERVAL_NO_WAIT);
      }
   private:
      PRFileDesc* mSocket;
      SocketOutputStream* mOutputStream;
      SocketInputStream* mInputStream;

   };

}


#endif
