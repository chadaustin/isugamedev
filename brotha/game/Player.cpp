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
 * Date modified: $Date: 2002-03-29 14:13:42 $
 * Version:       $Revision: 1.5 $
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
      : mName("Player"), mAccelerate(false), mBrake(false), mTurnLeft(false),
        mTurnRight(false)
   {
   }

   Player::Player( const std::string& name )
      : mName(name), mAccelerate(false), mBrake(false), mTurnLeft(false),
        mTurnRight(false)
   {
   }

   Player::~Player() {
   }

   void Player::setAccelerate( bool flag ) {
      mAccelerate = flag;
   }

   bool Player::isAccelerating() const {
      return mAccelerate;
   }

   void Player::setBrake( bool flag ) {
      mBrake = flag;
   }

   bool Player::isBraking() const {
      return mBrake;
   }

   void Player::setTurnLeft( bool flag ) {
      mTurnLeft = flag;
   }

   bool Player::isTurningLeft() const {
      return mTurnLeft;
   }

   void Player::setTurnRight( bool flag ) {
      mTurnRight = flag;
   }

   bool Player::isTurningRight() const {
      return mTurnRight;
   }

   const std::string& Player::getName() const {
      return mName;
   }

   void Player::setName( const std::string& name ) {
      mName = name;
   }
}
