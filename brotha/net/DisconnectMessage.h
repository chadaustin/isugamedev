/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_DISCONNECT_MESSAGE_H
#define NET_DISCONNECT_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   class DisconnectMessage : public Message {
   public:
      PRUint32 getType() const {
         return Disconnect;
      }

      PRUint32 getSize() {
         return 0;//getVarSize(mUsername) + getVarSize(mPassword);
      }

      void serialize(OutputStream& os) {
      }

      void deserialize(InputStream& is) {
      }
   };

} // namespace net

#endif // NET_DISCONNECT_MESSAGE_H
