/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:
#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

#include "MessageQueue.h"
#include "ReadThread.h"
#include "WriteThread.h"
#include "Socket.h"

namespace net {
   class Connection {
   public:
      Connection(Socket *socket);
      ~Connection();

      void send(Message *message);
      void read(std::vector<Message*> messages);
   private:
      Socket *m_socket;

      MessageQueue *m_writeQueue;
      MessageQueue *m_readQueue;

      ReadThread *m_readThread;
      WriteThread *m_writeThread;
   };
} // namespace net

#endif // NET_CONNECTION_H
