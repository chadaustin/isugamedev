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
 * File:          $RCSfile: Socket.h,v $
 * Date modified: $Date: 2002-02-26 00:51:07 $
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
#if !defined(Socket_H)
#define Socket_H

#include <winsock2.h>
#include <string>

#if defined(_WIN32)
   #if !defined(errno)
      #define errno WSAGetLastError
   #endif
#else
   #define ioctlsocket ioctl
#endif

namespace net {

class Socket {
protected:
   SOCKET m_socket;
   struct sockaddr_in m_addrIn;
   long m_port;
   unsigned int m_polltime;

public:
   Socket();
	virtual ~Socket();

   static int getLastError();
   
   bool create(SOCKET &sock, SOCKADDR &addr);
   bool open(std::string host, long port);
   static bool initSockAddrIn(std::string &host, long port, SOCKADDR_IN &addrIn);
   void close();

   long getRecieveSize();
   bool setSocketNonBlocking();
   long send(void* buffer, unsigned long bytes2write, unsigned int timeout);
   long recieve(void* buffer, unsigned long bytes2read, unsigned int timeout);
   bool ioControl(long cmd, unsigned long *argp);

   bool isOpen();
};

} // namespace net

#endif
