/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_SOCKET_H
#define NET_SOCKET_H


#include <prio.h>
#include <prnetdb.h>
#include <string.h>
#include "SocketOutputStream.h"
#include "SocketInputStream.h"
#include "SocketException.h"


namespace net {

   class Socket {
   public:
      // XXXaegis this should probably be private
      Socket(PRFileDesc* fd) {
         mOutputStream = 0;
         mInputStream = 0;
         mSocket = fd;
      }

      ~Socket() {
         delete mOutputStream;
         delete mInputStream;
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

         // HACK: TODO: uhh ... yea, AF_INET = 2 in windows atleast
         addr.inet.family = 2; // PR_FamilyInet() typically AF_INET;
         addr.inet.port   = PR_htons(port);

         status = PR_Connect(mSocket, &addr, PR_INTERVAL_NO_TIMEOUT);
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
         PR_Send(mSocket, buffer, size, 0, PR_INTERVAL_NO_TIMEOUT);
      }
   private:
      PRFileDesc* mSocket;
      SocketOutputStream* mOutputStream;
      SocketInputStream* mInputStream;

   };

}


#endif
