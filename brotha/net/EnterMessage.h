/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_ENTER_MESSAGE_H
#define NET_ENTER_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Clients will send this to join the game as a particular type of user
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

      PRUint32 getType() {
         return Enter;
      }

      PRUint32 getSize() {
         return getVarSize(mCode);
      }

      void serialize(OutputStream& os) {
         os << mCode;
      }

      void deserialize(InputStream& is) {
         is >> mCode;
      }

      const EnterCode getCode() {
         return (EnterCode)mCode;
      }
   private:
      PRUint32 mCode;
   };

}

#endif
