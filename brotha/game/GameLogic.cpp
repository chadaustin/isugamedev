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
 * Date modified: $Date: 2002-05-03 07:18:34 $
 * Version:       $Revision: 1.25 $
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
#include "xml/DataManager.h"
#include <gmtl/Containment.h>

namespace game
{
   GameLogic::GameLogic() {
   }

   GameLogic::~GameLogic() {
   }

   void GameLogic::update(float time) {
      gmtl::Point3f oPosition;
      gmtl::Spheref oSphere;

      // Handle inputs from the various players
      PlayerList::iterator itr;
      for (itr = mPlayer.begin(); itr != mPlayer.end(); ++itr) {
         Player* p = *itr;
         processInput(p, time);
      }

      for (unsigned int i=0; i < mObject.size(); i++){
         // compute new position
         oPosition = mObject[i]->getPosition() + (mObject[i]->getVelocity() * time);
         oSphere = mObject[i]->getSphere();

         // update position
         mObject[i]->setPosition(oPosition);
         oSphere.setCenter(oPosition);
         mObject[i]->setSphere(oSphere);
      }

      GameLogic::updateStats();

      for (unsigned int i=0; i < mObject.size(); i++){
         for (unsigned int j=0; j < mObject.size(); j++){
            if (gmtl::isInVolume(mObject[i]->getSphere(), mObject[j]->getSphere()) && i != j){
               mObject[i]->setHealth(mObject[i]->getHealth() - 15);
               mObject[j]->setHealth(mObject[j]->getHealth() - 15);
            }
         }
         if (mObject[i]->isDestroyed()){
            std::cout<< "YOU ARE DEAD" << std::endl;
         }
      }
   }

   void GameLogic::updateStats(){

      data::Player* dPlayer;
      data::Gang* dGang;
      std::ostringstream out;
      Player* currPlayer;
      std::string coins, kills, deaths;

      data::BrothaData& dBroth = data::DataManager::instance().getData();
      data::GangList& gangs = dBroth.getGangList();

      for (unsigned int i=0; i < gangs.size(); i++){
         /// update players xml data
         dGang = dBroth.getGang(gangs[i]->getName());
         data::PlayerList& gangPlayers = dGang->getPlayerList();
         for (unsigned int j=0; j < gangPlayers.size();j++){

            dPlayer = dGang->getPlayer(gangPlayers[j]->getName());
            currPlayer = GameLogic::getPlayer(dPlayer->getName());

            // make sure the player exists
            if (currPlayer != NULL){
               std::ostringstream out1;
               std::ostringstream out2;
               std::ostringstream out3;

               out1 << currPlayer->getKills();
               out2 << currPlayer->getDeaths();
               out3 << currPlayer->getCoins();

               dPlayer->setStat("kills", out1.str());
               dPlayer->setStat("deaths", out2.str());
               dPlayer->setStat("coins", out3.str());
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

   std::vector<Player*>& GameLogic::getPlayers() {
      return mPlayer;
   }

   std::vector<Object*>& GameLogic::getObjects() {
      return mObject;
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

   Object* GameLogic::getObject(const Object::UID& uid) {
      ObjectListItr itr = mObject.begin();
      for (itr = mObject.begin(); itr != mObject.end(); ++itr) {
         Object* obj = (*itr);
         if (obj->getUID() == uid) {
            return obj;
         }
      }
      return NULL;
   }

   void GameLogic::outputList() {
      for (unsigned int i=0; i < mPlayer.size(); i++){
         std::cout << mPlayer[i]->getName() << std::endl;
      }
   }

   void GameLogic::getStats(Player* player) {
      data::BrothaData& dBroth = data::DataManager::instance().getData();
      data::Player* dPlayer;
      int coins, kills, deaths;

      if (dBroth.getPlayer(player->getName()) != NULL){
         dPlayer = dBroth.getPlayer(player->getName());

         std::istringstream iss1 (dPlayer->getStat("coins"), std::istringstream::in);
         std::istringstream iss2 (dPlayer->getStat("kills"), std::istringstream::in);
         std::istringstream iss3 (dPlayer->getStat("deaths"), std::istringstream::in);

         iss1 >> coins;
         iss2 >> kills;
         iss3 >> deaths;

         player->setCoins(coins);
         player->setKills(kills);
         player->setDeaths(deaths);
      }
   }

   void GameLogic::processInput(Player* player, float dt) {
      std::cout<<"processInput for "<<player->getName()<<" with dt="<<dt<<std::endl;
      // Gets the forward vehicle
      const Object::UID& vehicleUID = player->getVehicle();
      Object* vehicle = getObject(vehicleUID);
//      gmtl::Vec3f forward = vehicle->getForward();
      gmtl::Vec3f forward(0,0,-1);
      float speed = 3.7f;

      float angSpeed = 30.0f * 180.0f / 3.141579f;

      // handle acceleration
      if (player->mIsAccelerating) {
         gmtl::Vec3f newV = vehicle->getVelocity() + (forward * (speed * dt));
         vehicle->setVelocity(newV);
      }
      if (player->mIsBraking) {
         vehicle->setVelocity(vehicle->getVelocity() - (forward * (speed * dt)));
      }
      if (player->mIsHandBraking) {
         /// @todo implement hand braking
         std::cout<<"Hand Braking (not implemented)!"<<std::endl;
      }
      if (player->mIsTurningLeft) {
//         vehicle->setAngularVelocity(vehicle->getAngularVelocity() + (angSpeed * dt));
      }
      if (player->mIsTurningRight) {
//         vehicle->setAngularVelocity(vehicle->getAngularVelocity() - (angSpeed * dt));
      }
   }
}
