/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#include "SocketOutputStream.h"
#include "Socket.h"

namespace net {

   void SocketOutputStream::write(void* buffer, int size) {
      int totalWrite = 0;
      int write = 0;
      while(size != totalWrite) {
         write = m_socket->write((char*)buffer+totalWrite, size);
         // if we wrote some bytes
         if(write > 0) {
            totalWrite += write;
         } else { // if we didn't write any (0) or got an error (-1)
            return;
         }
      }
   }

} // namespace net
