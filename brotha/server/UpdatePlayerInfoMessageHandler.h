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
 * File:          $RCSfile: UpdatePlayerInfoMessageHandler.h,v $
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
            //case (net::UpdatePlayerInfoMessage::ACCELERATION):
            //   player->mIsAccelerating = (uMsg->getOn() != 0);
            //   break;
            case (net::UpdatePlayerInfoMessage::BRAKE):
               player->mIsBraking = (uMsg->getOn() != 0);
               break;
            case (net::UpdatePlayerInfoMessage::HANDBRAKE):
               player->mIsHandBraking = (uMsg->getOn() != 0);
               break;
            case (net::UpdatePlayerInfoMessage::SHOOT):
               ///@todo do something with this
               break;
            case (net::UpdatePlayerInfoMessage::TURNRIGHT):
               player->mIsTurningRight = (uMsg->getOn() != 0);
               break;
            case (net::UpdatePlayerInfoMessage::TURNLEFT):
               player->mIsTurningLeft = (uMsg->getOn() != 0);
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
