#ifndef CLIENT_SERVER_CONNECTION_H
#define CLIENT_SERVER_CONNECTION_H


#include <string>
#include "net/NetMgr.h"


namespace client {

   /**
    * This class is responsible for maintaining the connection to the
    * server.
    */
   class ServerConnection {
   public:
      ServerConnection();
      ~ServerConnection();

      void connect(const std::string& host, int port);

      bool isConnected() {
         return mIsConnected;
      }

      void readAll(net::NetMgr::MsgList& msgs);
      void send(net::Message* msg);

   private:
      net::NetMgr*        mNetMgr;
      net::NetMgr::ConnID mConnID;

      bool mIsConnected;
   };

}


#endif
