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
 * File:          $RCSfile: AppState.h,v $
 * Date modified: $Date: 2002-03-29 16:35:49 $
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
#ifndef CLIENT_APP_STATE_H
#define CLIENT_APP_STATE_H

#include <memory>
#include "net/Message.h"
#include <iostream>

namespace client
{
   class BrothaApp;

   /**
    * Interface for classes that manage app state changes in the Brotha
    * application. Since there are various states we want to be able to easily
    * manage the complexity of supporting different behavior for the app when in
    * different states. This class implements the State pattern. (GoF)
    */
   class AppState {
   protected:
      /// This class is abstract. Instantiate a subclass instead.
      AppState() {}
   public:
      virtual ~AppState() {}

      /**
       * Handles the given message and updates the given application based on
       * the results.
       *
       * @return  the pointer to the next state or NULL if there should be no
       *          change
       */
      virtual std::auto_ptr<AppState> handleMessage(const net::Message* msg,
                                               BrothaApp* app) {
         return std::auto_ptr<AppState>(NULL);
      }

      /**
       * Does any generalized work not relating the to processing of messages
       * based on the amount of time that has passed since the last frame.
       *
       * @return  the pointer to the next state or NULL if there should be no
       *          change
       */
      virtual std::auto_ptr<AppState> update(BrothaApp* app) {
         return std::auto_ptr<AppState>(NULL);
      }
   };

   class ConnectedState;

   /**
    * @todo document :)
    */
   class InGameState : public AppState {
   public:
      InGameState() {  };
      virtual ~InGameState() {}

      virtual std::auto_ptr<AppState> handleMessage(const net::Message* msg,
         BrothaApp* app) {return std::auto_ptr<AppState>(NULL);}
   };

   /**
    * @todo document :)
    */
   class SyncState : public AppState {
   public:
      SyncState() {  };
      virtual ~SyncState() {}

      virtual std::auto_ptr<AppState> handleMessage(const net::Message* msg,
                                                BrothaApp* app);
   };

   /**
    * Expects an OK ack from the server in response to the login request
    * Then expects a Enter message from the server to tell us where to go
    */
   class JoinAsAckWaitState : public AppState {
   public:
      JoinAsAckWaitState() { m_gotOk = false; };
      virtual ~JoinAsAckWaitState() {}

      virtual std::auto_ptr<AppState> handleMessage(const net::Message* msg,
                                                BrothaApp* app);

      bool m_gotOk;
   };

   /**
    * Expects an OK ack from the server in response to the login request.
    */
   class LoginAckWaitState : public AppState {
   public:
      virtual ~LoginAckWaitState() {}

      /**
       * Process the ack from the login request. Error out all other messages.
       */
      virtual std::auto_ptr<AppState> handleMessage(const net::Message* msg,
                                               BrothaApp* app);
   };

   /**
    * Manages the client in the connected state.
    */
   class ConnectedState : public AppState {
   public:
      virtual ~ConnectedState() {}

      /// Start the login process with the server
      virtual std::auto_ptr<AppState> update(BrothaApp* app);
   };

   /**
    * Manages the client in the unconnected state.
    */
   class NotConnectedState : public AppState {
   public:
      virtual ~NotConnectedState() {}

      /**
       * Just log onto the server when the application has told us to.
       *
       * @todo Check for error conditions
       */
      virtual std::auto_ptr<AppState> update(BrothaApp* app);
   };

}

#endif

