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
 * File:          $RCSfile: GameLogic.cpp,v $
 * Date modified: $Date: 2002-05-01 23:01:54 $
 * Version:       $Revision: 1.15 $
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
#include "GameLogic.h"
#include <algorithm>
#include <gmtl/VecOps.h>
#include <sstream>

namespace game
{
   GameLogic::GameLogic() {
   }

   GameLogic::~GameLogic() {
   }

   void GameLogic::update(float time){ 
      gmtl::Vec3f oPosition;

      for (unsigned int i=0; i < mObject.size(); i++){
         // compute new position
         oPosition = mObject[i]->getPosition() + (mObject[i]->getVelocity() * time);

         // update position
         mObject[i]->setPosition(oPosition);
      }

      GameLogic::updateStats();

         /// @todo collision detection
         /// @todo update player attributes (health, kills, etc)  
   }

   void GameLogic::updateStats(){
      data::BrothaData* dBroth;
      data::Player* dPlayer;
      data::Gang* dGang;
      std::ostringstream out;
      Player* currPlayer;
      PlayerListItr Itr;
      mGang = dBroth->getGangList();

      for (unsigned int i=0; i < mGang.size(); i++){
         /// update players xml data
         dGang = dBroth->getGang(mGang[i]->getName());
         mGangPlayer = dGang->getPlayerList();
         for (unsigned int j=0; j < mGangPlayer.size();j++){
                        
            dPlayer = dGang->getPlayer(mGangPlayer[j]->getName());
            currPlayer = GameLogic::getPlayer(dPlayer->getName());
            
            if (currPlayer != NULL){
               out << currPlayer->getKills();
               dPlayer->setStat("Kills", out.str()); 
               out << currPlayer->getHealth();
               dPlayer->setStat("Health", out.str());
               out << currPlayer->getCoins();
               dPlayer->setStat("Coins", out.str());
            }// end if
         }// end for
      }// end for
   }

   void GameLogic::add(Player* player){

      // make sure player is not equal to null
      assert (player != NULL && "Cannot add a NULL player!");

      // add player to the vector
      mPlayer.push_back(player);
      std::cout << "Player added." << std::endl;
   }

   void GameLogic::remove(Player* player) {
      PlayerListItr Itr;

      // find the player to delete and set to iterator 
      Itr = std::find(mPlayer.begin(),mPlayer.end(),player);
      
      // makes sure object exists, then removes if it does
      if (Itr != mPlayer.end()){
         mPlayer.erase(Itr);
      }
   }

   void GameLogic::add(Object* object) {
      assert ( object != NULL && "Cannot add a Null object!" );

      // add object to vector
      mObject.push_back(object);
   }

   void GameLogic::remove(Object* object) {
      ObjectListItr Itr;

      // find the object to remove and set to iterator
      Itr = std::find(mObject.begin(), mObject.end(), object);
      
      // makes sure object exists and removes if it does
      if(Itr != mObject.end()){
         mObject.erase(Itr);
      }
   }

   Player* GameLogic::getPlayer(const std::string& name) {
      PlayerListItr itr = mPlayer.begin();
      for (itr = mPlayer.begin(); itr != mPlayer.end(); ++itr) {
         Player* player = (*itr);
         if (player->getName() == name) {
            return player;
         }
      }
      return NULL;
   }

   void GameLogic::outputList() {
      for (unsigned int i=0; i < mPlayer.size(); i++){
         std::cout << mPlayer[i]->getName() << std::endl;
      }
   }
}
