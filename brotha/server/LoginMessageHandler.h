/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef LOGIN_MESSAGE_HANDLER_H
#define LOGIN_MESSAGE_HANDLER_H

#include "MessageHandler.h"

namespace server {
   class LoginMessageHandler : public MessageHandler {
   public:
      LoginMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~LoginMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         net::LoginMessage *mMsg = (net::LoginMessage*)mMsg;
         /// @todo actual authentication
         if(1) {
            // let game know about this possible player
            m_brothaGame->add(new game::Player(mMsg->getUsername()), cID);
            // send the connection an OK message saying they are authenticated
            m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);
         } else {
            m_netMgr->send(new net::OKMessage(net::OKMessage::GENERIC_ERROR), cID);
         }
      };
   };
}

#endif // LOGIN_MESSAGE_HANDLER_H
