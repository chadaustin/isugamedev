/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "thread/Thread.h"
#include "net/MessageQueue.h"

namespace server {
   class GameServer : public thread::Thread {
   public:
      GameServer(net::MessageQueue* write, net::MessageQueue* read);
      virtual ~GameServer();

      virtual void run();
   private:
      net::MessageQueue* m_writeQueue;
      net::MessageQueue* m_readQueue;
   };
} // namespace server

#endif // GAME_SERVER_H