/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#include "SocketOutputStream.h"
#include "Socket.h"

namespace net {

   void SocketOutputStream::write(void* buffer, int size) {
      int write = 0;
      while(size != write) {
         write += m_socket->write((char*)buffer+write, size);
      }
   }

} // namespace net
