/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef RESYNC_MESSAGE_HANDLER_H
#define RESYNC_MESSAGE_HANDLER_H

#include "MessageHandler.h"

namespace server {
   class ResyncMessageHandler : public MessageHandler {
   public:
      ResyncMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~ResyncMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         m_brothaGame->resync(cID);
      };
   };
}

#endif // RESYNC_MESSAGE_HANDLER_H
