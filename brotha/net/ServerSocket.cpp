
#include "serversocket.h"

ServerSocket::ServerSocket(long _numQueued)
   :m_numQueued(_numQueued) {
}

ServerSocket::~ServerSocket(void) {
   close();
}

bool ServerSocket::open(long port) {
   std::string host = "localhost";

   // get socket
   m_socket = socket(PF_INET, SOCK_STREAM, 0);
   if(m_socket == INVALID_SOCKET)
      return false;

   // init address in
   initSockAddrIn(host, port, m_addrIn);

   // bind socket
   if(bind(m_socket, (const SOCKADDR*)&m_addrIn, sizeof(m_addrIn)) == SOCKET_ERROR) {
      // getLastError = Error Code
      return false;
   }
   return true;
}

bool ServerSocket::listen() {
   if(::listen(m_socket, m_numQueued) != 0) {
      // getLastError = Error Code
      return false;
   } else {
      return true;
   }
}

bool ServerSocket::accept(Socket &socket) {
   SOCKADDR addr;
   int size = sizeof(addr);
   memset(&addr, 0, sizeof(addr));

   SOCKET sock = ::accept(m_socket, &addr, &size);
   if(sock == INVALID_SOCKET) {
      // getLastError = Error Code
      return false;
   } else {
      socket.create(sock, addr);
      return true;
   }
}

