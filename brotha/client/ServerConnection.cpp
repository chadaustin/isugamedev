#include "ServerConnection.h"


namespace client {

   ServerConnection::ServerConnection() {
      mNetMgr = new net::NetMgr;
      mConnID = -1;
      mIsConnected = false;
   }

   ServerConnection::~ServerConnection() {
      delete mNetMgr;
      mConnID = -1;
      mIsConnected = false;
   }

   void ServerConnection::connect(const std::string& host, int port) {
      std::auto_ptr<net::Socket> socket(new net::Socket(host.c_str(), port));
      mConnID = mNetMgr->handleSocket(socket);
      mIsConnected = true;
   }

   void ServerConnection::readAll(net::NetMgr::MsgList& msgs) {
      /// @todo catch exceptions and close the connection?
      if (isConnected()) {
         mNetMgr->readAll(msgs);
      }
   }

   void ServerConnection::send(net::Message* msg) {
      /// @todo catch exceptions and close the connection?
      if (isConnected()) {
         mNetMgr->send(msg, mConnID);
      }
      /// @todo  delete the msg?
   }

}
