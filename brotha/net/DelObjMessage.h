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
    * Server will send this to notify that clients should delete an object
    */
   class DelObjMessage : public Message {
   public:
      DelObjMessage() {
      }

      PRUint32 getType() const {
         return DelObj;
      }

      PRUint32 getSize() {
         return net::sizes::getVarSize(mObjectID);
      }

      void serialize(OutputStream& os) {
         os << mObjectID;
      }

      void deserialize(InputStream& is) {
         is >> mObjectID;
      }
   private:
      PRUint32 mObjectID;
   };

}

#endif
