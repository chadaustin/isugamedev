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
 * File:          $RCSfile: BrothaGame.cpp,v $
 * Date modified: $Date: 2002-05-03 07:18:34 $
 * Version:       $Revision: 1.24 $
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
#include "xml/Player.h"
#include <vector>

namespace server {
   BrothaGame::BrothaGame(net::NetMgr *netMgr) {
      m_netMgr = netMgr;
      mGameTime.start();
   }

   BrothaGame::~BrothaGame() {
   }

   void BrothaGame::sendToAll( net::Message* msg, bool onlyInGame ) {
      // we want to send only to those clients actually in the game
      if(onlyInGame) {
         for(PlayerMapIter iter=mPlayers.begin();iter!=mPlayers.end();++iter) {
            if(!m_netMgr->send(msg, iter->second)) {
               // an error on send means that the connection is no longer
               // let us remember to remove this connection
               mClosedConnections.insert(iter->second);
            }
         }
      } else { // we want to send to everyone
         for(PlayerConnectionMapIter iter=mConnectedPlayers.begin();iter!=mConnectedPlayers.end();++iter) {
            if(!m_netMgr->send(msg, iter->first)) {
               // an error on send means that the connection is no longer
               // let us remember to remove this connection
               mClosedConnections.insert(iter->first);
            }
         }
      }
   }

   void BrothaGame::update() {
      // remove players for connections that have closed
      for(ClosedConnectionMapIter iter=mClosedConnections.begin();iter!=mClosedConnections.end();++iter) {
         removeConnection(*iter);
      }

      // Do a frame in the game logic if we haven't paused the game
      if (! isPaused()) {
         mGameTime.update();
         // Convert to seconds
         float dt = mGameTime.getElapsedTime() / 1000.0f;
         mLogic.update(dt);
      }

      // Run through all objects in game and broadcast their updated data
      typedef std::vector<game::Object*> ObjList;
      ObjList& objs = mLogic.getObjects();
      for (ObjList::iterator itr = objs.begin(); itr != objs.end(); ++itr) {
         net::UpdateObjMessage *msg = new net::UpdateObjMessage(*itr);
         sendToAll(msg, true);
      }

      // Run through all players in game and broadcast their updated data
      typedef std::vector<game::Player*> PlayerList;
      PlayerList& players = mLogic.getPlayers();
      for (PlayerList::iterator itr = players.begin(); itr != players.end(); ++itr) {
         net::UpdatePlayerMessage *msg = new net::UpdatePlayerMessage(*itr);
         sendToAll(msg, true);
      }


      /// @todo do a frame in the game
      /// @todo for each object that is modified broadcast to everyone

      /// fake frame (just move all players y pos up 1) and send to all players

      /*for(PlayerMapIter iter=mPlayers.begin();iter!=mPlayers.end();++iter) {
         game::Player* player = getPlayer(iter->second);
         gmtl::Vec<PRFloat64, 3> pos = player->getObject()->getPosition();
         if(pos[1] <= -5) {
            pos[0]+=0.1;
         } else {
            pos[1]-=0.1;
         }
         player->getObject()->setPosition(pos);
         net::UpdatePlayerMessage *msgP = new net::UpdatePlayerMessage(getPlayer(iter->second));

         sendToAll(msgP, true);
      }
	  */
   }

   void BrothaGame::addPlayer( game::Player* player, net::NetMgr::ConnID cID ) {
      assert( player != NULL && "Cannot add a NULL player!" );
      mConnectedPlayers[cID] = player;

      // notify everyone else of this player being added to the game
//      net::AddPlayerMessage *msg = new net::AddPlayerMessage(player);
//      sendToAll(msg, true);
   }

   void BrothaGame::removePlayer( game::Player* player ) {
     PlayerMapIter delPlayer = mPlayers.find( getUID(player) );
      if(delPlayer != mPlayers.end()) {
         game::Player::UID uid = delPlayer->first;
         std::cout<<"Removed player: "<<uid<<std::endl;
         // if the player actually exists in the game, remove them from it
         mPlayers.erase(delPlayer);

         // remove the player (and his vehicle) from the logic too
         mLogic.remove(player);
         const game::Object::UID& vehicleUID = player->getVehicle();
         mLogic.remove(mLogic.getObject(vehicleUID));

         // notify everyone else that user was removed
         net::DelPlayerMessage *msg = new net::DelPlayerMessage(uid);
         sendToAll(msg, true);
      }
   }

   void BrothaGame::removeConnection( net::NetMgr::ConnID cID ) {
      PlayerConnectionMapIter delConnection = mConnectedPlayers.find(cID);
      if(delConnection != mConnectedPlayers.end()) {
         game::Player *player = delConnection->second;

         std::cout<<"Removed connection: "<<delConnection->first<<std::endl;
         // if the connection actually exists, remove it from the map
         mConnectedPlayers.erase(delConnection);

         // remove the player from the game if they happen to be in it
         removePlayer(player);
      }
   }

   game::Player* BrothaGame::getPlayer( game::Player::UID uid ) {
      PlayerMapIter iter = mPlayers.find(uid);
      if ( iter != mPlayers.end() ) {
         return getPlayer( iter->second );
      }
      return NULL;
   }

   game::Player* BrothaGame::getPlayer( net::NetMgr::ConnID cID ) {
      PlayerConnectionMapIter iter = mConnectedPlayers.find(cID);
      if ( iter != mConnectedPlayers.end() ) {
         return iter->second;
      }
      return NULL;
   }

   net::NetMgr::ConnID BrothaGame::getConnectionID( game::Player* player ) {
      game::Player::UID uid = player->getUID();
      return getConnectionID( uid );
   }

   net::NetMgr::ConnID BrothaGame::getConnectionID( game::Player::UID uid ) {
      PlayerMapIter iter = mPlayers.find( uid );
      if ( iter != mPlayers.end() ) {
         return iter->second;
      }
      return -1;
   }

   game::Player::UID BrothaGame::getUID( net::NetMgr::ConnID cID ) {
      PlayerConnectionMapIter iter = mConnectedPlayers.find( cID );
      if( iter != mConnectedPlayers.end() ) {
         return getUID( iter->second );
      }
      return game::Player::UNKNOWN;
   }

   game::Player::UID BrothaGame::getUID( game::Player *player ) {
      return player->getUID();
   }

   void BrothaGame::joinPlayer( net::NetMgr::ConnID cID ) {
      std::cout<<"Player "<<getUID(cID)<<" on connection "<<cID<<" has joined the game."<<std::endl;
      mPlayers[getUID(cID)] = cID;

      game::Player* player = getPlayer(cID);
      assert(player != NULL && "Tried to join a NULL player");

      // Create the game player object and his vehicle
      game::Object* obj = new game::Object();
      obj->setModel("models/hovertank_body.obj");
      player->setVehicle(obj->getUID());

      // Add player and object to the game
      mLogic.add(obj);
      mLogic.add(player);

      /// @todo notify all the other connections that a new player exists
   }

   void BrothaGame::resync( net::NetMgr::ConnID cID) {
      std::cout<<"resync"<<std::endl;
      // send players
      for(PlayerMapIter iter=mPlayers.begin();iter!=mPlayers.end();++iter) {
         net::AddPlayerMessage *msgP = new net::AddPlayerMessage(getPlayer(iter->second));
         std::cout<<"\tAdd Player: "<<iter->first<<std::endl;
         m_netMgr->send(msgP, cID);
      }
      // send objects
      typedef std::vector<game::Object*> ObjList;
      ObjList& objs = mLogic.getObjects();
      for (ObjList::iterator itr = objs.begin(); itr != objs.end(); ++itr) {
         net::AddObjMessage *msg = new net::AddObjMessage(*itr);
         std::cout<<"\tAdd Object: "<<(*itr)->getUID()<<std::endl;
         sendToAll(msg, true);
      }

      // end resync
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
      return mGameTime.isStopped();
   }

   const game::GameTimer& BrothaGame::getGameTimer() const {
      return mGameTime;
   }

   game::GameLogic& BrothaGame::getLogic() {
      return mLogic;
   }
}
