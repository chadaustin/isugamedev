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
 * File:          $RCSfile: SellModMessage.h,v $
 * Date modified: $Date: 2002-05-03 07:01:48 $
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

#ifndef NET_SELL_MOD_MESSAGE_H
#define NET_SELL_MOD_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Client will send this to sell a mod
    */
   class SellModMessage : public Message {
   public:
      SellModMessage(std::string carName = "", std::string modName = "", int modLevel = 0) {
         mCarName = carName;
         mModName = modName;
         mModLevel = modLevel;
      }

      PRUint32 getType() const {
         return BuyMod;
      }

      PRUint32 getSize() {
         return sizes::getVarSize(mCarName) + 
                sizes::getVarSize(mModName) +
                sizes::getVarSize(mModLevel);
      }

      std::string& getCarName() {
         return mCarName;
      }

      std::string& getModName() {
         return mModName;
      }

      int getModLevel() {
         return (int)mModLevel;
      }

      void serialize(OutputStream& os) {
         os << mCarName << mModName << mModLevel;
      }

      void deserialize(InputStream& is) {
         is >> mCarName >> mModName >> mModLevel;
      }

   private:
      std::string mCarName;
      std::string mModName;
      PRFloat64 mModLevel;
   };

}

#endif
