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
 * File:          $RCSfile: RequestGarageDataMessageHandler.h,v $
 * Date modified: $Date: 2002-05-03 08:03:42 $
 * Version:       $Revision: 1.3 $
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

#ifndef REQ_GARAGE_DATA_MESSAGE_HANDLER_H
#define REQ_GARAGE_DATA_MESSAGE_HANDLER_H

#include "MessageHandler.h"
#include "net/GarageDataMessage.h"

namespace server {
   class RequestGarageDataMessageHandler : public MessageHandler {
   public:
      RequestGarageDataMessageHandler(BrothaGame* game, net::NetMgr* netMgr)
         : MessageHandler(game, netMgr) {
      }

      ~RequestGarageDataMessageHandler() {}

      virtual void handleMessage(net::Message *msg, net::NetMgr::ConnID cID) {
         // get the main data and the player the user entered
         data::BrothaData& data = data::DataManager::instance().getData();
         data::Player* player = data.getPlayer(m_brothaGame->getPlayer(cID)->getName());
         data::CarTypeList* carlist = &data.getCarTypes();
         data::ModTypeList* modlist = &data.getModTypes();

         // send the data
         m_netMgr->send(new net::GarageDataMessage(player, carlist, modlist), cID);
      };
   };
}

#endif // JOIN_AS_MESSAGE_HANDLER_H
