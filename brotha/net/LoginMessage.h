#ifndef NET_LOGIN_MESSAGE_H
#define NET_LOGIN_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"


namespace net {

   class LoginMessage : public Message {
   public:
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