/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_SOCKET_H
#define NET_SOCKET_H


#include <prio.h>
#include <prnetdb.h>
#include <prerror.h>
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
         close();

         delete mOutputStream;
         delete mInputStream;
      }

      Socket(const char* hostname, int port) {
         mOutputStream = 0;
         mInputStream = 0;

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

         addr.inet.family = PR_AF_INET;
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

      int read(void* buffer, int size) {
         int read = PR_Recv(mSocket, buffer, size, 0, PR_INTERVAL_NO_TIMEOUT);
         // if the peer closed the connection or we were interrupted
         if(read == 0) {
            throw SocketException("Peer closed connection");
         } else if(read < 0 && PR_GetError() == PR_PENDING_INTERRUPT_ERROR) {
            throw SocketException("Interrupt occurred");
         } else if(read < 0) {
            throw SocketException("Unknown error");
         }
         return read;
      }

      int write(void* buffer, int size) {
         int sent = PR_Send(mSocket, buffer, size, 0, PR_INTERVAL_NO_TIMEOUT);
         // if we were interrupted
         if(sent < 0 && PR_GetError() == PR_PENDING_INTERRUPT_ERROR) {
            throw SocketException("Interrupt occurred");
         } else if(sent < 0) {
            throw SocketException("Unknown error");
         }
         return sent;
      }

      void close() {
         PRStatus status = PR_Close(mSocket);
         if( status != PR_SUCCESS) {
            throw SocketException("Close failed");
         }
      }
   private:
      PRFileDesc* mSocket;
      SocketOutputStream* mOutputStream;
      SocketInputStream* mInputStream;

   };

}


#endif
