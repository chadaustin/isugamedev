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
 * Date modified: $Date: 2002-04-22 05:37:09 $
 * Version:       $Revision: 1.12 $
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

namespace game {
   const Player::UID Player::UNKNOWN = 0;

   Player::Player()
      : mName("Player"), mAccelerate(0), mBrake(0), mTurnAngle(0) {
      mUID = UIDMgr::getInstance().reserveID();
      mObject = new Object();
   }

   Player::Player( const std::string& name )
      : mName(name), mAccelerate(0), mBrake(0), mTurnAngle(0) {
      mUID = UIDMgr::getInstance().reserveID();
      mObject = new Object();
   }

   Player::~Player() {
      delete mObject;
      UIDMgr::getInstance().releaseID( mUID );
   }

   const Player::UID& Player::getUID() const {
      return mUID;
   }

   void Player::setAcceleration( PRFloat64 newAcc ) {
      mAccelerate = newAcc;
   }

   PRFloat64 Player::getAcceleration() const {
      return mAccelerate;
   }

   void Player::setBrake( PRFloat64 newBreak ) {
      mBrake = newBreak;
   }

   PRFloat64 Player::getBrake() const {
      return mBrake;
   }

   PRFloat64 Player::getTurnAngle() const {
      return mTurnAngle;
   }

   void Player::setTurnAngle( PRFloat64 newAngle ) {
      mTurnAngle = newAngle;
   }

   const std::string& Player::getName() const {
      return mName;
   }

   void Player::setName( const std::string& name ) {
      mName = name;
   }

   Object* Player::getObject() {
      return mObject;
   }

   PRUint32 Player::getSize() {
      return net::sizes::getVarSize(mUID)
           + net::sizes::getVarSize(mName) 
           + net::sizes::getVarSize(mAccelerate)
           + net::sizes::getVarSize(mBrake)
           + net::sizes::getVarSize(mTurnAngle)
           + mObject->getSize();
   }

   void Player::serialize(net::OutputStream& os) {
      mObject->serialize(os);
      os << mUID << mName << mAccelerate << mBrake << mTurnAngle;
   }

   void Player::deserialize(net::InputStream& is) {
      mObject->deserialize(is);
      is >> mUID >> mName >> mAccelerate >> mBrake >> mTurnAngle;
   }

}
