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
 * File:          $RCSfile: EnterMessage.h,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.8 $
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

#ifndef NET_ENTER_MESSAGE_H
#define NET_ENTER_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Server will send this to notify that clients should change locations
    */
   class EnterMessage : public Message {
   public:
      enum EnterCode {
         GAME, ///< Tell client to go to the game
         GARAGE ///< Tell client to go to the garage
      };
   public:
      EnterMessage(const EnterCode& code = GARAGE) 
         : mCode( code ) {
      }

      PRUint32 getType() const {
         return Enter;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mCode);
      }

      void serialize(OutputStream& os) {
         os << mCode;
      }

      void deserialize(InputStream& is) {
         is >> mCode;
      }

      const EnterCode getCode() const {
         return (EnterCode)mCode;
      }
   private:
      PRUint32 mCode;
   };

}

#endif
