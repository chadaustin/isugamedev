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
 * File:          $RCSfile: AppState.cpp,v $
 * Date modified: $Date: 2002-03-29 15:48:38 $
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
#include "AppState.h"
#include "BrothaApp.h"

namespace client
{
   std::auto_ptr<AppState> LoginAckWaitState::handleMessage(
               const net::Message* msg,
               BrothaApp* app)
   {
      // Check message type
      if ( msg->getType() == net::OK ) {
         // Message is Ack from login msg
         const net::OKMessage* okMsg = (const net::OKMessage*)(msg);
         if ( okMsg->getCode() == net::OKMessage::OKAY ) {
            std::cout<<"Login successful"<<std::endl;

            // send request to join game
            app->getNetMgr()->send(new net::JoinAs(net::JoinAs::PLAYER), app->getConnID());
            return std::auto_ptr<AppState>(new LoggedInState());
         } else {
            std::cout<<"Login failed"<<std::endl;
            return std::auto_ptr<AppState>(new ConnectedState());
         }
      } else {
         std::cout<<"ERROR: Got the wrong message type"<<std::endl;
         /// @todo raise an error
      }
      return std::auto_ptr<AppState>(new ConnectedState());
   }

   std::auto_ptr<AppState> ConnectedState::update(BrothaApp* app) {
      //Fire off a login message
      net::Message* msg = new net::LoginMessage(
            app->getLoginName(),
            app->getLoginPass()
      );
      app->getNetMgr()->send(msg, app->getConnID());
      return std::auto_ptr<AppState>(new LoginAckWaitState());
   }

   std::auto_ptr<AppState> NotConnectedState::update(BrothaApp* app) {
      // Only connect when the app has told us to do so
      if (app->doConnect()) {
         std::cout<<"Connecting"<<std::endl;
         try {
            // Create the socket and tell the NetMgr to deal with it
            std::auto_ptr<net::Socket> socket(
                  new net::Socket(app->getServerIP().c_str(), app->getServerPort())
            );
            net::NetMgr::ConnID connID = app->getNetMgr()->handleSocket(socket);
            app->setServerConn(connID);
            app->setIsConnected(true);
            // move to the connected state
            return std::auto_ptr<AppState>(new ConnectedState());
         }
         catch (net::SocketException& ex) {
            std::cout<<"Failed to connect: "<<ex.what()<<std::endl;
            // mark as false
            app->setIsConnected(false);
            return std::auto_ptr<AppState>(NULL);
         }
      }

      // don't change state if we didn't try to connect
      return std::auto_ptr<AppState>(NULL);
   }
}
