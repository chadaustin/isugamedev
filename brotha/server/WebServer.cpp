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
 * File:          $RCSfile: WebServer.cpp,v $
 * Date modified: $Date: 2002-04-29 03:59:13 $
 * Version:       $Revision: 1.11 $
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

#include "WebServer.h"
#include "..\xml\xmlpersist.h"
#include "..\xml\brothadata.h"
#include "..\xml\HtmlGen.h"

namespace server {
   WebServer::WebServer()
      : m_serverSocket(8800) {
   }

   WebServer::~WebServer() {
   }

   void WebServer::run() {
	   dataxml::load("test.xml"); //remove this
      while(PR_AtomicIncrement(&mKillMe)) {
         // accept new client connections, inform the NetMgr about them
         net::Socket *sock = m_serverSocket.accept();
         if(sock != NULL) {
            processRequest(sock, readRequest(sock));
            delete sock;
         }

         PR_AtomicDecrement(&mKillMe);
      }
   }

   std::string WebServer::readRequest(net::Socket *socket) {
      std::string retVal;
      while(1) {
         char buffer[256];
         int bytesRead = socket->read(buffer, 256);
         retVal.resize(retVal.length() + bytesRead);
         std::copy(buffer, buffer+bytesRead, retVal.begin());
         if(retVal.find("\r\n\r\n") != std::string::npos) {
            break;
         }
         continue;
      }
      return retVal;
   }

   void WebServer::processRequest(net::Socket *socket, const std::string &str) {
      /// @todo actually process request and generate dynamic response :)

      std::string response = "HTTP/1.0 200\r\n";
	  response += "Content-Type: text/html\r\n\r\n";
	  response += reports::GenerateReportFromHTTP(str);
      sendResponse(socket, response);
   }

   void WebServer::sendResponse(net::Socket *socket, const std::string &str) {
      int written = 0;
      int toWrite = (int)str.length();
      char buffer[64];
      while(toWrite > 0) {
         using namespace std;
         int write = min(toWrite, 64);
         std::copy(str.begin() + written, str.begin() + written + write, buffer);
         socket->write(buffer, write);
         written += write;
         toWrite -= write;
      }
   }

} // namespace server