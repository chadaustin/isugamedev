/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_SOCKET_OUTPUT_STREAM_H
#define NET_SOCKET_OUTPUT_STREAM_H

#include "Socket.h"

namespace net {

   class SocketOutputStream : public OutputStream {
   public:
      SocketOutputStream(Socket *socket) {
         m_socket = socket;
      }

      virtual ~SocketOutputStream() { }

      virtual void write(void* buffer, int size) {
         m_socket.write(buffer, size);
      }
   private:
      net::Socket *m_socket;
   };

} // namespace net


#endif // NET_SOCKET_OUTPUT_STREAM_H
