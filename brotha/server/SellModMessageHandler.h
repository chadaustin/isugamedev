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
 * File:          $RCSfile: SellModMessageHandler.h,v $
 * Date modified: $Date: 2002-05-03 09:53:07 $
 * Version:       $Revision: 1.2 $
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

#ifndef SELL_MOD_MESSAGE_HANDLER_H
#define SELL_MOD_MESSAGE_HANDLER_H

#include "MessageHandler.h"

namespace server {
   class SellModMessageHandler : public MessageHandler {
   public:
      SellModMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~SellModMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         net::SellModMessage *mMsg = (net::SellModMessage*)msg;

         // get the main data and the player the user is
         data::BrothaData& data = data::DataManager::instance().getData();
         data::Player* player = data.getPlayer(m_brothaGame->getPlayer(cID)->getName());

         /// @todo maybe add some validation (i.e. cost, car exists, etc.)

         data::Car* car = player->getCar(mMsg->getCarName());
         if(car != NULL) {
            car->removeMod(mMsg->getModName());
         }

         // send the good response
         m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);
      };
   };
}

#endif // SELL_MOD_MESSAGE_HANDLER_H
