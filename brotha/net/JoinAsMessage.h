/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_JOIN_AS_MESSAGE_H
#define NET_JOIN_AS_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Clients will send this to join the game as a particular type of user
    */
   class JoinAsMessage : public Message {
   public:
      enum JoinAsCode {
         PLAYER, ///< Join game as player
         SPECTATOR ///< Join game as spectator
      };
   public:
      /**
       * Creates a new JoinAs message with the default join as code SPECTATOR.
       */
      JoinAsMessage(const JoinAsCode& code = SPECTATOR)
         : mCode( code ) {
      }

      PRUint32 getType() const {
         return JoinAs;
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

      const JoinAsCode getCode() {
         return (JoinAsCode)mCode;
      }
   private:
      PRUint32 mCode;
   };

}

#endif
