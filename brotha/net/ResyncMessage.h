/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_RESYNC_MESSAGE_H
#define NET_RESYNC_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   /**
    * Clients will send this to request a resync
    */
   class ResyncMessage : public Message {
   public:
      ResyncMessage() {
      }

      PRUint32 getType() const {
         return Resync;
      }

      PRUint32 getSize() {
         return 0;
      }

      void serialize(OutputStream& os) {
      }

      void deserialize(InputStream& is) {
      }
   };

}

#endif
