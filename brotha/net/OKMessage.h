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
 * File:          $RCSfile: OKMessage.h,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
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

#ifndef NET_OK_MESSAGE_H
#define NET_OK_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {
   /**
    * Describes an acknowledgement message that is normally used in response to
    * a question asked across the network.
    */
   class OKMessage : public Message {
   public:
      /// The response codes supported for an OKMessage.
      enum ResponseCode {
         GENERIC_ERROR,   ///< Generic error
         OKAY             ///< Generic ok
      };
   public:
      /**
       * Creates a new OK message with the response code OK.
       */
      OKMessage()
         : mCode( OKAY )
      {
         /// @todo get the standard response string
         mDesc = "fixme";
      }

      /**
       * Creates a new OK message with the given response code.
       */
      OKMessage( const ResponseCode& code )
         : mCode( code )
      {
         /// @todo get the standard response string
         mDesc = "fixme";
      }

      PRUint32 getType() const {
         return OK;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mCode) + net::sizes::getVarSize(mDesc);
      }

      void serialize(OutputStream& os) {
         os << mCode << mDesc;
      }

      void deserialize(InputStream& is) {
         is >> mCode >> mDesc;
      }

      /**
       * Gets the response code associated with this message.
       *
       * @return  the response code
       */
      const ResponseCode getCode() const {
         return (ResponseCode)mCode;
      }

      /**
       * Gets the response description associated with this message.
       *
       * @return  the response description
       */
      const std::string& getDescription() const {
         return mDesc;
      }

   private:
      /// The response code
      PRUint32 mCode;

      /// The string description
      std::string mDesc;
   };

}


#endif
