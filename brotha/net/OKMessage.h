/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

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

      PRUint32 getType() {
         return MSG_OK;
      }

      PRUint32 getSize() {
         return getVarSize(mDesc);
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
      const ResponseCode& getCode() {
         return *(ResponseCode*)&mCode;
      }

      /**
       * Gets the response description associated with this message.
       *
       * @return  the response description
       */
      const std::string& getDescription() {
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
