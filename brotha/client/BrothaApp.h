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
 * Date modified: $Date: 2002-04-26 13:17:34 $
 * Version:       $Revision: 1.19 $
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
#include "ServerConnection.h"
#include "State.h"

namespace client
{
   /**
    * Warn-a-Brotha interface with GameKernel.
    */
   class BrothaApp
   {
   public:
      BrothaApp();
      ~BrothaApp();

      // called externally by the driving loop
      void update(int elapsedTime);
      void draw();
      void resize(int width, int height);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      // switch the current state object with another
      void invokeStateTransition(State* state);

      void sendMessage(net::Message* msg);

      void connectToServer(const std::string& server, int port);

      /**
       * Sets which player is on the local machine. If player is NULL,
       * don't draw anything.
       *
       * @param player     the player corresponding to the local player
       */
      void setLocalPlayer(game::Player* player) {
         mLocalPlayer = player;
      }

      /**
       * Gets the player on the local machine. If there is no local
       * player, this method will return NULL.
       *
       * @return  the local player or NULL if there is no player on the local
       *          machine
       */
      game::Player* getLocalPlayer() {
         return mLocalPlayer;
      }

      game::BrothaGame& getGame() {
         return mGame;
      }

      bool getFirstMsg(net::Message*& msg) {
         if(!mMsgList.empty()) {
            msg = mMsgList[0].first;
            mMsgList.erase(mMsgList.begin());
            return true;
         }
         return false;
      }

   private:
      /// Current state of the game.
      State* mCurrentState;

      State* mTransitionState;

      /// Our lovely game instance.
      game::BrothaGame mGame;

      /// The local player.
      game::Player* mLocalPlayer;

      /// Facade for connection with server.
      ServerConnection mServerConnection;

      /// read Message List
      net::NetMgr::MsgList mMsgList;

      //@{
      /// Current dimensions of the window.
      int mWidth;
      int mHeight;
      //@}

      /// Sound music and effects manager.
      sound::SoundManager* mSoundMgr;
   };
}

#endif
