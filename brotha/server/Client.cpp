#include "Client.h"

namespace server {
   Client::Client(net::Socket *socket, net::MessageQueue *readQueue) {
      m_socket = socket;

      m_clientServer = new ClientServer(readQueue);
      m_clientServer->start();
   }

   Client::~Client() {
      m_clientServer->stop();
      delete m_clientServer;
   }
} // namespace server
