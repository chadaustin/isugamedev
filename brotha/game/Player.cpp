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
 * Date modified: $Date: 2002-03-29 17:23:01 $
 * Version:       $Revision: 1.8 $
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
   Player::Player()
      : mName("Player"), mAccelerate(0), mBrake(0), mTurnAngle(0)
   {
   }

   Player::Player( const std::string& name )
      : mName(name), mAccelerate(0), mBrake(0), mTurnAngle(0)
   {
   }

   Player::~Player() {
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

   PRUint32 Player::getType() const {
      return PlayerObject;
   }

   PRUint32 Player::getSize() {
      return getVarSize(mName) + getVarSize(mAccelerate) + getVarSize(mBrake)
         + getVarSize(mTurnAngle) + Object::getSize();
   }

   void Player::serialize(net::OutputStream& os) {
      Object::serialize(os);
      os << mName << mAccelerate << mBrake << mTurnAngle;
   }

   void Player::deserialize(net::InputStream& is) {
      Object::deserialize(is);
      is >> mName >> mAccelerate >> mBrake >> mTurnAngle;
   }

}
