/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#include "SocketInputStream.h"
#include "Socket.h"

namespace net {

   void SocketInputStream::read(void* buffer, int size) {
      int totalRead = 0;
      int read = 0;
      while(size != totalRead) {
         read = m_socket->read((char*)buffer+totalRead, size);
         // if we read some bytes
         if(read > 0) {
            totalRead += read;
         } else { // if we didn't read any (0) or got an error (-1)
            return;
         }
      }
   }

} // namespace net
