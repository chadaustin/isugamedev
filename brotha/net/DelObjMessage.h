/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_DEL_OBJ_MESSAGE_H
#define NET_DEL_OBJ_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Clients will send this to join the game as a particular type of user
    */
   class DelObjMessage : public Message {
   public:
      DelObjMessage() {
      }

      PRUint32 getType() {
         return DelObj;
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
