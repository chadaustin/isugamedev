/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#include "SocketInputStream.h"
#include "Socket.h"

namespace net {

   void SocketInputStream::read(void* buffer, int size) {
      while(size != 0) {
         size -= m_socket->read(buffer, size);
      }
   }

} // namespace net
