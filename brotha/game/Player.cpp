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
 * File:          $RCSfile: Player.cpp,v $
 * Date modified: $Date: 2002-04-29 02:13:43 $
 * Version:       $Revision: 1.16 $
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
#include "Player.h"
#include <algorithm>

namespace game {
   const Player::UID Player::UNKNOWN = 0;

   Player::Player()
      : mName("Player"), mBrake(0), mTurnAngle(0), mKills(0){
      mUID = UIDMgr::getInstance().reserveID();
   }

   Player::Player( const std::string& name )
      : mName(name), mBrake(0), mTurnAngle(0), mKills(0){
      mUID = UIDMgr::getInstance().reserveID();
   }

   Player::~Player() {
      UIDMgr::getInstance().releaseID( mUID );
   }

   const Player::UID& Player::getUID() const {
      return mUID;
   }

   void Player::setBrake( PRFloat64 newBreak ){
      mBrake = newBreak;
   }

   gmtl::Vec3f Player::getVelocity(){
      return mVelocity;
   }

   gmtl::Vec3f Player::getPosition(){
      return mPosition;
   }

   void Player::setPosition(gmtl::Vec3f newPosition){
      mPosition = newPosition;
   }

   void Player::setVelocity(gmtl::Vec3f newVelocity){
      mVelocity = newVelocity;
   }

   PRFloat64 Player::getBrake() const {
      return mBrake;
   }

   PRFloat64 Player::getTurnAngle() const {
      return mTurnAngle;
   }
   
   void Player::setTurnAngle(PRFloat64 newAngle){
      mTurnAngle = newAngle;
   }

   const std::string& Player::getName() const {
      return mName;
   }

   void Player::setName( const std::string& name ){
      mName = name;
   }

   void Player::addCar(Car* car){
      assert ( car != NULL && "Cannot add a Null car!" );

      // add car to vector
      mCars.push_back(car);
   }

   void Player::removeCar(Car* car){
      CarListItr Itr;

      // find the car to remove and set to iterator
      Itr = std::find(mCars.begin(), mCars.end(), car);
      
      // makes sure car exists and removes if it does
      if(Itr != mCars.end()){
         mCars.erase(Itr);
      }
   }

   PRUint32 Player::getSize(){
      return net::sizes::getVarSize(mUID)
           + net::sizes::getVarSize(mName) 
           + net::sizes::getVarSize(mBrake)
           + net::sizes::getVarSize(mTurnAngle);
   }

   void Player::serialize(net::OutputStream& os){
      os << mUID << mName << mBrake << mTurnAngle;
   }

   void Player::deserialize(net::InputStream& is){
      is >> mUID >> mName >> mBrake >> mTurnAngle;
   }

}
