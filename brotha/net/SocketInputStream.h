/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_SOCKET_INPUT_STREAM_H
#define NET_SOCKET_INPUT_STREAM_H


#include "InputStream.h"

namespace net {

   class Socket;
   class SocketInputStream : public InputStream {
   public:
      SocketInputStream(Socket *socket) {
         m_socket = socket;
      }

      virtual ~SocketInputStream() { }

      virtual void read(void* buffer, int size);
   private:
      net::Socket *m_socket;
   };

} // namespace net


#endif // NET_SOCKET_INPUT_STREAM_H
