/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_LOGIN_MESSAGE_H
#define NET_LOGIN_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   class LoginMessage : public Message {
   public:
      LoginMessage() {
      }

      LoginMessage(std::string username, std::string password) {
         mUsername = username;
         mPassword = password;
      }

      int getType() {
         return MSG_LOGIN;
      }

      void serialize(OutputStream& os) {
         os << mUsername << mPassword;
      }

      void deserialize(InputStream& is) {
         is >> mUsername >> mPassword;
      }

   private:
      std::string mUsername;
      std::string mPassword;
   };

}


#endif
