/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_DEL_PLAYER_MESSAGE_H
#define NET_DEL_PLAYER_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Server will send this to notify that clients should delete a player
    */
   class DelPlayerMessage : public Message {
   public:
      DelPlayerMessage( game::Player::UID uid = 0xFFFF )
         : mUID(uid)
      { }

      PRUint32 getType() const {
         return DelPlayer;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mUID);
      }

      void serialize(OutputStream& os) {
         os << mUID;
      }

      void deserialize(InputStream& is) {
         is >> mUID;
      }
   private:
      PRUint32 mUID;
   };

}

#endif
