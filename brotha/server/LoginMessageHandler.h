/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef LOGIN_MESSAGE_HANDLER_H
#define LOGIN_MESSAGE_HANDLER_H

#include "MessageHandler.h"

class LoginMessageHandler {
public:
   LoginMessageHandler(game::BrothaGame* game, net::NetMgr* netMgr)
      : MessageHandler(game, netMgr {
   }

   ~LoginMessageHandler() {}

   virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
      /// @actual authentication
      if(1) {
         m_netMgr->send(new net::OKMessage(net::OKMessage::ResponseCode::OKAY));
      } else {
         m_netMgr->send(new net::OKMessage(net::OKMessage::ResponseCode::ERROR));
      }
   };
};

#endif // LOGIN_MESSAGE_HANDLER_H
