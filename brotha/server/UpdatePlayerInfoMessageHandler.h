/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef UPDATE_PLAYER_INFO_MESSAGE_HANDLER_H
#define UPDATE_PLAYER_INFO_MESSAGE_HANDLER_H

#include "MessageHandler.h"

namespace server {
   class UpdatePlayerInfoMessageHandler : public MessageHandler {
   public:
      UpdatePlayerInfoMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~UpdatePlayerInfoMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         net::UpdatePlayerInfoMessage* uMsg = (net::UpdatePlayerInfoMessage*)msg;
         // get player based off of connection
         game::Player* player = m_brothaGame->getPlayer(cID);
         // update info
         switch(uMsg->getUpdateWhat()) {
            case (net::UpdatePlayerInfoMessage::ACCELERATION):
               player->setAcceleration(uMsg->getUpdateTo());
               break;
            case (net::UpdatePlayerInfoMessage::HANDBRAKE):
               ///@todo do something with this
               break;
            case (net::UpdatePlayerInfoMessage::SHOOT):
               ///@todo do something with this
               break;
            case (net::UpdatePlayerInfoMessage::TURN):
               player->setTurnAngle(uMsg->getUpdateTo());
               break;
            case (net::UpdatePlayerInfoMessage::WEAPON):
               ///@todo do something with this
               break;
            default:
               break;
         }
      };
   };
}

#endif // UPDATE_PLAYER_INFO_MESSAGE_HANDLER_H
