/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#include "SocketInputStream.h"
#include "Socket.h"

namespace net {

   void SocketInputStream::read(void* buffer, int size) {
      int read = 0;
      while(size != read) {
         read += m_socket->read((char*)buffer+read, size);
      }
   }

} // namespace net
