#ifndef NET_SOCKET_H
#define NET_SOCKET_H


#include <prio.h>
#include <prnetdb.h>
#include <string.h>
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


namespace net {

  class Socket {
  public:
    Socket(const char* hostname, int port) {
      mSocket = PR_NewTCPSocket();

      PRNetAddr addr;
      memset(&addr, 0, sizeof(addr));

      // assert?
      PR_SUCCESS == PR_StringToNetAddr(hostname, &addr);

      addr.inet.family = PR_FamilyInet();
      addr.inet.port   = port;

      // assert?
      PR_SUCCESS == PRConnect(mSocket, &addr, PR_INTERVAL_NO_TIMEOUT);
    }

    InputStream* getInputStream() {
    }

    OutputStream* getOutputStream() {
    }
    
  }

}


#endif
