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
 * File:          $RCSfile: AddPlayerMessage.h,v $
 * Date modified: $Date: 2002-05-01 19:05:47 $
 * Version:       $Revision: 1.11 $
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

#ifndef NET_ADD_PLAYER_MESSAGE_H
#define NET_ADD_PLAYER_MESSAGE_H


#include <string>
#include "game/Player.h"
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Server will send this to notify that clients should add a player
    */
   class AddPlayerMessage : public Message {
   public:
      AddPlayerMessage(game::Player* player = NULL) {
         m_player = player;
      }

      PRUint32 getType() const {
         return AddPlayer;
      }

      PRUint32 getSize() {
         if(m_player != NULL) {
            return m_player->getSize();
         } else {
            return 0;
         }
      }

      game::Player* getPlayer() {
         return m_player;
      }

      void serialize(OutputStream& os) {
         if(m_player != NULL) {
            m_player->serialize(os);
         }
      }

      void deserialize(InputStream& is) {
         if (m_player == NULL) {
            m_player = new game::Player();
         }
         m_player->deserialize(is);
      }
   private:
      game::Player *m_player;
   };

}

#endif
