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
 * File:          $RCSfile: BrothaGame.cpp,v $
 * Date modified: $Date: 2002-03-30 21:04:27 $
 * Version:       $Revision: 1.7 $
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
#include "BrothaGame.h"

namespace server {
   BrothaGame::BrothaGame(net::NetMgr *netMgr) {
      m_netMgr = netMgr;
   }

   void BrothaGame::update() {
      /// @todo do a frame in the game
      /// for each object that is modified broadcast to everyone


      /// fake frame (just move all players y pos up 1) and send to all players
      for(PlayerMapIter iter=mPlayers.begin();iter!=mPlayers.end();++iter) {
         game::Player* player = iter->second;
         gmtl::Vec<PRFloat64, 3> pos = player->getObject()->getPosition();
         pos[1]-=0.1;
         player->getObject()->setPosition(pos);
         net::UpdatePlayerMessage *msgP = new net::UpdatePlayerMessage(iter->second);
         m_netMgr->sendToAll(msgP);
      }
   }

   void BrothaGame::add( game::Player* player, net::NetMgr::ConnID cID ) {
      assert( player != NULL && "Cannot add a NULL player!" );
      mConnectedPlayers[cID] = player;
   }

   net::NetMgr::ConnID BrothaGame::getConnectionID( game::Player* player ) {
      for(PlayerConnectionMapIter iter=mConnectedPlayers.begin();iter!=mConnectedPlayers.end();++iter) {
         if(player == iter->second) {
            return iter->first;
         }
      }
      return -1;
   }

   game::Player* BrothaGame::getPlayer( game::Player::UID uid ) {
      PlayerMap::iterator itr = mPlayers.find(uid);
      if ( itr != mPlayers.end() ) {
         return itr->second;
      }
      return NULL;
   }

   void BrothaGame::joinPlayer( net::NetMgr::ConnID cID ) {
      game::Player *player = mConnectedPlayers[cID];
      mPlayers[player->getUID()] = player;

      /// @todo notify all the other connections that a new player exists
   }

   void BrothaGame::resync( net::NetMgr::ConnID cID) {
      // send players
      for(PlayerMapIter iter=mPlayers.begin();iter!=mPlayers.end();++iter) {
         bool isYou = (cID == getConnectionID(iter->second));
         net::AddPlayerMessage *msgP = new net::AddPlayerMessage(iter->second, isYou);
         m_netMgr->send(msgP, cID);
      }
      // send objects
      m_netMgr->send(new net::OKMessage(net::OKMessage::OKAY), cID);
   }

   void BrothaGame::setPaused( bool pause ) {
      if ( pause ) {
         mGameTime.stop();
      } else {
         mGameTime.start();
      }
   }

   bool BrothaGame::isPaused() const {
      return ( ! mGameTime.isStopped() );
   }

   const game::GameTimer& BrothaGame::getGameTimer() const {
      return mGameTime;
   }
}
