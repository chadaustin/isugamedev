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
      enum UpdateWhat {
         ACCELERATION, ///< Acceleration
         HANDBRAKE, ///< Hand break (on/off)
         TURN, ///< Angle of turn
         WEAPON, ///< Change weapon
         SHOOT ///< Shoot weapon
      };

   public:
      UpdatePlayerInfoMessage(const UpdateWhat& what = TURN, const PRFloat64& to = 0.0)
         : mUpdateWhat(what), mUpdateTo(to)
      {
      }

      PRUint32 getType() const {
         return UpdatePlayerInfo;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mUpdateWhat) + net::sizes::getVarSize(mUpdateTo);
      }

      void serialize(OutputStream& os) {
         os << mUpdateWhat << mUpdateTo;
      }

      void deserialize(InputStream& is) {
         is >> mUpdateWhat >> mUpdateTo;
      }
   private:
      PRUint32 mUpdateWhat;
      PRFloat64 mUpdateTo;
   };

}

#endif
