/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_MESSAGE_H
#define NET_MESSAGE_H


#include "InputStream.h"
#include "OutputStream.h"

namespace net {

   class Message {
   public:
      virtual ~Message() { }
      virtual PRUint32 getType() = 0;
      virtual PRUint32 getSize() = 0;
      virtual void serialize(OutputStream& os) = 0;
      virtual void deserialize(InputStream& os) = 0;
   protected:
      PRUint32 getVarSize(PRUint32 &var) {
         return PRUint32(sizeof(PRUint32));
      }

      PRUint32 getVarSize(std::string &var) {
         return PRUint32(sizeof(PRUint32) + var.length());
      }
   };

}


#endif
