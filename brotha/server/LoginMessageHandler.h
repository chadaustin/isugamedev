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
 * File:          $RCSfile: LoginMessageHandler.h,v $
 * Date modified: $Date: 2002-05-01 19:05:47 $
 * Version:       $Revision: 1.10 $
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
         net::LoginMessage *mMsg = (net::LoginMessage*)msg;

         // get the main data and the player the user entered
         data::BrothaData data = m_brothaGame->getDataManager().getData();
         data::Player* player = data.getPlayer(mMsg->getUsername());

         if(player != NULL && player->getPassword().compare(mMsg->getPassword()) == 0) {
            // let game know about this possible player
            m_brothaGame->addPlayer(new game::Player(mMsg->getUsername()), cID);
            // send the connection an OK message saying they are authenticated
            m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);

            // let them know who they are
            m_netMgr->send(new net::AddPlayerMessage(m_brothaGame->getPlayer(cID)), cID);
         } else {
            m_netMgr->send(new net::OKMessage(net::OKMessage::GENERIC_ERROR), cID);
         }
      };
   };
}

#endif // LOGIN_MESSAGE_HANDLER_H
