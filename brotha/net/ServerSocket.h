/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
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
 * File:          $RCSfile: ServerSocket.h,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.13 $
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

#ifndef NET_SERVER_SOCKET_H
#define NET_SERVER_SOCKET_H


#include "Socket.h"


namespace net {

   class ServerSocket {
   public:
      ServerSocket(int port) {
         mSocket = PR_NewTCPSocket();
         if (!mSocket) {
            throw SocketException("Socket creation failed");
         }

         PRNetAddr addr;
         PRStatus status = PR_InitializeNetAddr(PR_IpAddrAny, port, &addr);
         if (status != PR_SUCCESS) {
            throw SocketException("Bind failed");
         }
      
         status = PR_Bind(mSocket, &addr);
         if (status != PR_SUCCESS) {
            throw SocketException("Bind failed");
         }

         status = PR_Listen(mSocket, 16);
         if (status != PR_SUCCESS) {
            throw SocketException("Listen failed");
         }
      }

      ~ServerSocket() {
         PRStatus status = PR_Close(mSocket);
         if( status != PR_SUCCESS) {
            throw SocketException("Close failed");
         }
      }

      Socket* accept() {
         PRNetAddr address;  // of connecting socket
         PRFileDesc* fd = PR_Accept(mSocket, &address, PR_INTERVAL_NO_TIMEOUT);
         return (fd ? new Socket(fd) : 0);
      }

   private:
      PRFileDesc* mSocket;
   };

}


#endif
