/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "BrothaGame.h"

namespace server {
   class MessageHandler {
   public:
      MessageHandler(BrothaGame* game, net::NetMgr* netMgr) {
         m_brothaGame = game;
         m_netMgr = netMgr;
      }

      virtual ~MessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) = 0;
   protected:
      BrothaGame* m_brothaGame;
      net::NetMgr* m_netMgr;
   };
}

#endif // MESSAGE_HANDLER_H
