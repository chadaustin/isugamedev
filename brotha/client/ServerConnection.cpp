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
 * File:          $RCSfile: ServerConnection.cpp,v $
 * Date modified: $Date: 2002-05-01 18:40:38 $
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
      // only connect we aren't already
      if(!isConnected()) {
         std::auto_ptr<net::Socket> socket(new net::Socket(host.c_str(), port));
         mConnID = mNetMgr->handleSocket(socket);
         mIsConnected = true;
      }
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
