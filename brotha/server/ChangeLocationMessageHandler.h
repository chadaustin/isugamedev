/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ChangeLocationMessageHandler.h,v $
 * Date modified: $Date: 2002-05-02 09:16:47 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */

#ifndef SERVER_CHANGE_LOCATION_MESSAGE_HANDLER_H
#define SERVER_CHANGE_LOCATION_MESSAGE_HANDLER_H

#include "MessageHandler.h"
#include "net/ChangeLocationMessage.h"

namespace server {
   class ChangeLocationMessageHandler : public MessageHandler {
   public:
      ChangeLocationMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~ChangeLocationMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         net::ChangeLocationMessage* clMsg = (net::ChangeLocationMessage*)msg;
         // Leave garage, enter the game
         if (clMsg->getLocation() == net::ChangeLocationMessage::GAME) {
            // join the player to the game and send the OK message
            m_brothaGame->joinPlayer(cID);
            m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);
         }
         // Leave game, enter garage
         else if (clMsg->getLocation() == net::ChangeLocationMessage::GARAGE) {
            m_brothaGame->removePlayer(m_brothaGame->getPlayer(cID));
            m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);
         }
         else {
            m_netMgr->send(new net::OKMessage(net::OKMessage::GENERIC_ERROR), cID);
         }
      }
   };
}

#endif // JOIN_AS_MESSAGE_HANDLER_H
