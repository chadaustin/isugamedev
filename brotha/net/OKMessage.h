/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_OK_MESSAGE_H
#define NET_OK_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   class OKMessage : public Message {
   public:
      int getType() {
         return MSG_OK;
      }

      void serialize(OutputStream& os) {
         os << std::string("OK");
      }

      void deserialize(InputStream& is) {
         std::string ok;
         is >> ok;
         // assert ok == "OK"
      }
   };

}


#endif
