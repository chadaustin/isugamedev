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
 * File:          $RCSfile: JoinAsMessageHandler.h,v $
 * Date modified: $Date: 2002-04-28 16:41:06 $
 * Version:       $Revision: 1.6 $
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

#ifndef JOIN_AS_MESSAGE_HANDLER_H
#define JOIN_AS_MESSAGE_HANDLER_H

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

            // tell the player to enter the garage
            m_netMgr->send(new net::EnterMessage(net::EnterMessage::GARAGE), cID);
//            /// @todo implement garage so I can tell the player to go there
//            // for now just send them straight to the game
//            m_netMgr->send(new net::EnterMessage(net::EnterMessage::GAME), cID);
            // assuming we did send the enter game, lets forward this to the resync operation
//            m_brothaGame->resync(cID);
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

#endif // JOIN_AS_MESSAGE_HANDLER_H
