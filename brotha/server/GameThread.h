/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include "thread/Thread.h"
#include "net/NetMgr.h"

namespace server {
   class GameThread : public thread::Thread {
   public:
      GameThread(net::NetMgr *netMgr);
      virtual ~GameThread();

      virtual void run();
   private:
      net::NetMgr* m_netMgr;
   };
} // namespace server

#endif // GAME_SERVER_H
