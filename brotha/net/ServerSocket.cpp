/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ServerSocket.cpp,v $
 * Date modified: $Date: 2002-03-02 13:08:31 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */
#include "ServerSocket.h"

namespace net {

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

long ServerSocket::select(unsigned int timeout) {
   long result = Socket::select(timeout);
   if(result==select_READ) {
      long length = getRecieveSize();
      result = (length==0 ? select_CONNECT : select_READ);
   }
   return result;
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

} // namespace net