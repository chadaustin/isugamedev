#ifndef NET_SERVER_SOCKET_H
#define NET_SERVER_SOCKET_H


#include "Socket.h"


namespace net {

  class ServerSocket {
  public:
    ServerSocket(int port) {
    }

    Socket* accept() {
      
    }

  private:
    PRFileDesc* mSocket;
  }

}


#endif
