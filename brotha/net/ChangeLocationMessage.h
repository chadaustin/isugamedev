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
 * File:          $RCSfile: ChangeLocationMessage.h,v $
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
#ifndef NET_CHANGE_LOCATION_MESSAGE_H
#define NET_CHANGE_LOCATION_MESSAGE_H

#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"

namespace net {

   /**
    * Clients will send this to join the game as a particular type of user
    */
   class ChangeLocationMessage : public Message {
   public:
      enum Location {
         GARAGE, ///< Client wishes to enter the garage
         GAME, ///< Join game as spectator
      };
   public:
      /**
       * Creates a new ChangeLocation message with the default location as
       * GARAGE.
       */
      ChangeLocationMessage(const Location& loc = GARAGE)
         : mLoc(loc) {
      }

      PRUint32 getType() const {
         return ChangeLocation;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mLoc);
      }

      void serialize(OutputStream& os) {
         os << mLoc;
      }

      void deserialize(InputStream& is) {
         is >> mLoc;
      }

      const Location getLocation() const {
         return (Location)mLoc;
      }
   private:
      PRUint32 mLoc;
   };

}

#endif
