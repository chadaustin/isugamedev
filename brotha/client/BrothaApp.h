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
 * File:          $RCSfile: BrothaApp.h,v $
 * Date modified: $Date: 2002-04-22 04:16:20 $
 * Version:       $Revision: 1.14 $
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
#ifndef CLIENT_BROTHA_APP_H
#define CLIENT_BROTHA_APP_H

#include <SDL/SDL.h>
#include "game/BrothaGame.h"
#include "net/NetMgr.h"
#include "net/JoinAsMessage.h"
#include "sound/SoundManager.h"
#include "AppState.h"
#include "Scene.h"

namespace client
{
   /**
    * Warn-a-Brotha interface with GameKernel.
    */
   class BrothaApp
   {
   public:
      /// Creates a new brotha app.
      BrothaApp();

      /// Cleans up resources used by this app.
      ~BrothaApp();

      void update(int elapsedTime);
      void draw();
      void resize(int width, int height);
      
      void processInput(SDLKey sym, bool keyDown);

      /**
       * Sets which player is on the local machine. If player is NULL, then it is
       * assumed that there is no local player and this is a dedicated server.
       *
       * @param player     the player corresponding to the local player
       */
      void setLocalPlayer(game::Player* player) {
         mLocalPlayer = player;
      }

      /**
       * Gets the player on the local machine. If there is no local player, as
       * could be the case on a dedicated server, this method will return NULL.
       *
       * @return  the local player or NULL if there is no player on the local
       *          machine
       */
      game::Player* getLocalPlayer() {
         return mLocalPlayer;
      }

      /**
       * Gets the network manager for this app.
       */
      net::NetMgr* getNetMgr() {
         return mNetMgr;
      }

      const std::string& getLoginName() const {return mName; }
      const std::string& getLoginPass() const { return mPass; }

      void setServerConn( net::NetMgr::ConnID id ) { mConnID = id; }
      bool setIsConnected( bool val ) { return mIsConnected; }
      net::NetMgr::ConnID getConnID() { return mConnID; }

      bool doConnect() { return true; }
      std::string getServerIP() { return "127.0.0.1"; }
      int getServerPort() { return 35791; }

      bool isInGame() { return mInGame; }
      void setInGame( bool val ) { mInGame = val; }

      game::BrothaGame& getGame() { return mGame; }

   public:
      /// Our lovely game instance
      game::BrothaGame mGame;

      /// Our gateway to the network interface
      net::NetMgr* mNetMgr;

      /// The connection to the server
      net::NetMgr::ConnID mConnID;

      /// The application state
      std::auto_ptr<AppState> mAppState;

      std::string mName, mPass;
      bool mIsConnected;
      bool mInGame;

      /// Sound music and effects manager.
      sound::SoundManager* mSoundMgr;
      
      int mWidth;
      int mHeight;

      /// The local player
      game::Player* mLocalPlayer;

      /// The scene with which the game is represented.
      Scene mScene;
   };
}

#endif
