/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_UPDATE_PLAYER_INFO_MESSAGE_H
#define NET_UPDATE_PLAYER_INFO_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Clients will send this to update player information
    */
   class UpdatePlayerInfoMessage : public Message {
   public:
      UpdatePlayerInfoMessage() {
      }

      PRUint32 getType() {
         return UpdatePlayerInfo;
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
   private:
      PRUint32 mCode;
   };

}

#endif
