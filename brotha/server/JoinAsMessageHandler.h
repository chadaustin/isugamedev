/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef JOIN_AS_MESSAGE_H
#define JOIN_AS_MESSAGE_H

#include "MessageHandler.h"

namespace server {
   class JoinAsMessageHandler : public MessageHandler {
   public:
      JoinAsMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~JoinAsMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         /// for the prototype we only want players
         net::JoinAsMessage* jMsg = (net::JoinAsMessage*)msg;
         if(jMsg->getCode() == net::JoinAsMessage::PLAYER) {
            m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);
         } else {
            m_netMgr->send(new net::OKMessage(net::OKMessage::GENERIC_ERROR), cID);
         }
      };
   };
}

#endif // JOIN_AS_MESSAGE_H
