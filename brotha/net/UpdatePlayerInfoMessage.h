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
         NOTHING, ///< Update nothing
         ACCELERATION, ///< Acceleration
         BRAKE, ///< Brake (-Acceleration)
         HANDBRAKE, ///< Hand break (on/off)
         TURNRIGHT, ///< Turn right
         TURNLEFT, ///< Turn left
         WEAPON, ///< Change weapon
         SHOOT ///< Shoot weapon
      };

   public:
      UpdatePlayerInfoMessage(const UpdateWhat& what = NOTHING, const PRFloat64& on = 0)
         : mUpdateWhat(what), mOn(on)
      {
      }

      PRUint32 getType() const {
         return UpdatePlayerInfo;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mUpdateWhat) + net::sizes::getVarSize(mOn);
      }

      const UpdateWhat getUpdateWhat() {
         return (UpdateWhat)mUpdateWhat;
      }

      const bool getOn() {
         return mOn;
      }

      void serialize(OutputStream& os) {
         os << mUpdateWhat << mOn;
      }

      void deserialize(InputStream& is) {
         is >> mUpdateWhat >> mOn;
      }
   private:
      PRUint32 mUpdateWhat;
      PRFloat64 mOn;
   };

}

#endif
