/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef UPDATE_PLAYER_INFO_MESSAGE_HANDLER_H
#define UPDATE_PLAYER_INFO_MESSAGE_HANDLER_H

#include "MessageHandler.h"

namespace server {
   class UpdatePlayerInfoMessageHandler : public MessageHandler {
   public:
      UpdatePlayerInfoMessageHandler(game::BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~UpdatePlayerInfoMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         net::UpdatePlayerInfo* uMsg = (net::UpdatePlayerInfo*)msg;
      };
   };
}

#endif // UPDATE_PLAYER_INFO_MESSAGE_HANDLER_H
