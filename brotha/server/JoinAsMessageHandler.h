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
            // join the player to the game and send the OK message
            m_brothaGame->joinPlayer(cID);
            m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);

            /// @todo implement garage so I can tell the player to go there
            // for now just send them straight to the game
            m_netMgr->send(new net::EnterMessage(net::EnterMessage::GAME), cID);
            // assuming we did send the enter game, lets forward this to the resync operation
            m_brothaGame->resync(cID);
         } else if (jMsg->getCode() == net::JoinAsMessage::SPECTATOR) {
            /// @todo join the spectator to the game and not error
            m_netMgr->send(new net::OKMessage(net::OKMessage::GENERIC_ERROR), cID);
         } else {
            // unknown player type, send error
            m_netMgr->send(new net::OKMessage(net::OKMessage::GENERIC_ERROR), cID);
         }
      };
   };
}

#endif // JOIN_AS_MESSAGE_H
