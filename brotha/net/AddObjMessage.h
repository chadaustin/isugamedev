/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_ADD_OBJ_MESSAGE_H
#define NET_ADD_OBJ_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Server will send this to notify that clients should add an object
    */
   class AddObjMessage : public Message {
   public:
      AddObjMessage() {
      }

      PRUint32 getType() const {
         return AddObj;
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
   private:
      PRUint32 mCode;
   };

}

#endif
