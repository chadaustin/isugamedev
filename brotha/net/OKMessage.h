#ifndef NET_OK_MESSAGE_H
#define NET_OK_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"

/*ripped from Aegis's LogonMessage.h file*/


namespace net {

  class OKMessage : public Message {
  public:
    OKMessage() {

    }

    int getType() {
      return MSG_OK;
    }

    void serialize(OutputStream& os) {
      os << "OK";
    }

    void deserialize(InputStream& is) {
      is >> mOK;
	  assert mOK == "OK";
    }

  private:
    std::string mOK;  //hehe 'mOK' :P
  };

}


#endif
