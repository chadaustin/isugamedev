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
 * File:          $RCSfile: Socket.cpp,v $
 * Date modified: $Date: 2002-02-26 00:42:13 $
 * Version:       $Revision: 1.3 $
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
#include "socket.h"

Socket::Socket(void)
   :m_socket(INVALID_SOCKET),
   m_port(),
   m_polltime(100) {

   #if defined( _WIN32 )
   // init startup for WinSocks 2.0
   WSADATA WSAData;
   WSAStartup( MAKEWORD(2,0), &WSAData );
   #endif
}

Socket::~Socket(void) {
   close();
}

int Socket::getLastError() {
   return WSAGetLastError();
}

bool Socket::create(SOCKET &sock, SOCKADDR &addr) {
		if ( sock == INVALID_SOCKET )
			return false;

		// get new socket
		memcpy(&m_addrIn, (SOCKADDR *) &addr, sizeof(addr));
		memcpy(&m_socket, &sock, sizeof(m_socket));

		return true;
}

bool Socket::open(std::string host, long port) {
   // get the socket
   m_socket = socket(PF_INET,SOCK_STREAM,0);
   if (m_socket == INVALID_SOCKET ) {
      return false;
   }

   // initialize address in
   m_port = port;
   initSockAddrIn(host, port, m_addrIn);

   // connect to socket
   if(connect(m_socket, (const SOCKADDR *) &m_addrIn, sizeof(m_addrIn)) == SOCKET_ERROR) {
      int error = getLastError();
      return false;
   }

   return true;
}

bool Socket::initSockAddrIn(std::string &host, long port, SOCKADDR_IN &addrIn) {
   // initialize socket in struct
   memset(&addrIn,0,sizeof(addrIn));

   addrIn.sin_family = AF_INET;

   if(!host.empty()) {
      LPHOSTENT phost;
      if((phost = gethostbyname(host.c_str())) != NULL) {
         memcpy((char FAR*)&(addrIn.sin_addr),phost->h_addr,phost->h_length);
      } else {
         addrIn.sin_addr.s_addr = inet_addr(host.c_str());
      }
   } else {
      addrIn.sin_addr.s_addr = htonl(INADDR_ANY);
   }

   addrIn.sin_port = htons((u_short)port);

   return true;
}

void Socket::close() {
   // close socket if it is open
   if(m_socket != INVALID_SOCKET) {
      closesocket(m_socket);
      m_socket = INVALID_SOCKET;
   }
}

long Socket::getRecieveSize() {
   // return no of bytes waiting
   // failure will return none
   long retval;
   if(ioControl(FIONREAD,(unsigned long*)&retval)) {
      return retval;
   } else {
      return 0;
   }
}

bool Socket::setSocketNonBlocking() {
   // set socket to non-blocking mode
   // only a guess, probably not finished :/
   unsigned long ioctl_option = -1;
   return ioControl(FIONBIO,&ioctl_option);
}

long Socket::send(void* buffer, unsigned long bytes2write, unsigned int timeout) {
   int bytesSent = 0;
   struct fd_set poll_obj;
   struct timeval timeVal;
   unsigned int time_taken = 0;
   char *tempPointer = (char*)buffer;

   FD_ZERO(&poll_obj);
   FD_SET(m_socket,&poll_obj);

   // wait m_polltime milliseconds each poll (select)
   timeVal.tv_sec  = (long)((m_polltime*1000) / 1000000); // seconds to wait
   timeVal.tv_usec = (long)((m_polltime*1000) % 1000000); // micro seconds to wait

   // attempt to write everything before a time out
   while(bytes2write > 0) {
      switch(select(0, (fd_set*)0, &poll_obj, (fd_set*)0, &timeVal)) {
         case SOCKET_ERROR: {
            // 'select' failed
            // getLastError = Error Code
            return bytesSent;
         } break;
         case 0: { // time limit expired
            // check to see if we are taking too long
            time_taken += m_polltime;
            if(time_taken >= timeout)
               bytes2write = 0; // if so, quit prematurely
         } break;
         case 1: { // 1 socket handle ready
            int numSent = ::send(m_socket, (char*)tempPointer, bytes2write, 0);
            if((numSent == SOCKET_ERROR) &&
                     ((getLastError() == WSAECONNRESET) ||
                     (getLastError() == WSAESHUTDOWN))) {
               bytes2write = 0;
            } else if((numSent > 0) ||
                     (getLastError() == WSAEWOULDBLOCK) ||
                     (getLastError() == WSAEINPROGRESS)) {
               bytes2write -= numSent;
               tempPointer += numSent;
               bytesSent += numSent;

               // check to see if we are taking too long
               time_taken += m_polltime;
               if(time_taken >= timeout)
                  bytes2write = 0; // if so, quit prematurely
            } else {
               // 'send' failed
               // getLastError = Error Code
               shutdown(m_socket, SD_SEND);
               bytes2write = 0;
            }
         } break;
         default:
            break;
      }
   }
   return bytesSent;
}

long Socket::recieve(void* buffer, unsigned long bytes2read, unsigned int timeout) {
   int bytesRead = 0;
   struct fd_set poll_obj;
   struct timeval timeVal;
   unsigned int time_taken = 0;
   char *tempPointer = (char*)buffer;

   FD_ZERO(&poll_obj);
   FD_SET(m_socket,&poll_obj);

   // wait m_polltime milliseconds each poll (select)
   timeVal.tv_sec  = (long)((m_polltime*1000) / 1000000); // seconds to wait
   timeVal.tv_usec = (long)((m_polltime*1000) % 1000000); // micro seconds to wait

   // attempt to read everything before a time out
   while(bytes2read > 0) {
      switch(select(0, &poll_obj, (fd_set*)0, (fd_set*)0, &timeVal)) {
         case SOCKET_ERROR: {
            // 'select' failed
            // getLastError = Error Code
            return bytesRead;
         } break;
         case 0: { // time limit expired
            // check to see if we are taking too long
            time_taken += m_polltime;
            if(time_taken >= timeout)
               bytes2read = 0; // if so, quit prematurely
         } break;
         case 1: { // 1 socket handle ready
            int numRead = recv(m_socket, (char*)tempPointer, bytes2read, 0);
            if((numRead == SOCKET_ERROR) &&
                     ((getLastError() == WSAECONNRESET) ||
                     (getLastError() == WSAESHUTDOWN))) {
               bytes2read = 0;
            } else if((numRead > 0) ||
                     (getLastError() == WSAEWOULDBLOCK) ||
                     (getLastError() == WSAEINPROGRESS)) {
               bytes2read -= numRead;
               tempPointer += numRead;
               bytesRead += numRead;

               // check to see if we are taking too long
               time_taken += m_polltime;
               if(time_taken >= timeout)
                  bytes2read = 0; // if so, quit prematurely
            } else {
               // 'recv' failed
               // getLastError = Error Code
               shutdown(m_socket, SD_SEND);
               bytes2read = 0;
            }
         } break;
         default:
            break;
      }
   }
   return bytesRead;
}

bool Socket::ioControl(long cmd, unsigned long *argp) {
   // perform the requested action
   long retval = ioctlsocket(m_socket,cmd,argp);
   if(retval == 0) {
      return true;
   } else {
      // do something with the error?
      return false;
   }
}

bool Socket::isOpen() {
   return (m_socket != INVALID_SOCKET);
}
