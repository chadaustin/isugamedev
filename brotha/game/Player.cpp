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
#include "Player.h"
#include <algorithm>

namespace game {
   const Player::UID Player::UNKNOWN = 0;

   Player::Player(const std::string& name)
      : mName(name)
      , mHealth(0)
      , mKills(0)
      , mDeaths(0)
      , mCoins(0)
      , mVehicle(Object::UNKNOWN)
      , mIsAccelerating(false)
      , mIsBraking(false)
      , mIsHandBraking(false)
      , mIsTurningLeft(false)
      , mIsTurningRight(false)
   {
      mUID = UIDMgr::getInstance().reserveID();
   }

   Player::~Player() {
      UIDMgr::getInstance().releaseID( mUID );
   }

   const Player::UID& Player::getUID() const {
      return mUID;
   }

   const Object::UID& Player::getVehicle() const {
      return mVehicle;
   }

   void Player::setVehicle(const Object::UID& vehicle) {
      mVehicle = vehicle;
   }

   const std::string& Player::getName() const {
      return mName;
   }

   void Player::setName(const std::string& name) {
      mName = name;
   }

   PRUint32 Player::getSize() {
      return net::sizes::getVarSize(mUID)
           + net::sizes::getVarSize(mName)
           + net::sizes::getVarSize(mHealth)
           + net::sizes::getVarSize(mVehicle);
   }

   void Player::serialize(net::OutputStream& os){
      os << mUID << mName << mHealth << mVehicle;
   }

   void Player::deserialize(net::InputStream& is){
      is >> mUID >> mName >> mHealth >> mVehicle;
   }
}
