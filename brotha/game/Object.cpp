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
 * File:          $RCSfile: Object.cpp,v $
 * Date modified: $Date: 2002-05-03 06:09:27 $
 * Version:       $Revision: 1.11 $
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
#include "Object.h"
#include <sstream>

namespace game {
   const Object::UID Object::UNKNOWN = 0;

   Object::Object()
      : mHealth(0) 
   {
      mUID = UIDMgr::getInstance().reserveID();
      std::ostringstream out;
      out << mUID;
      mName = out.str();
   }

   Object::~Object() {
      UIDMgr::getInstance().releaseID( mUID );
   }

   const Object::UID& Object::getUID() const {
      return mUID;
   }

   const std::string& Object::getName() const {
      return mName;
   }

   const std::string& Object::getModel() const {
      return mModel;
   }

   void Object::setModel(const std::string& model) {
      mModel = model;
   }

   PRUint32 Object::getType() {
      return NoObject;
   }

   PRUint32 Object::getSize() {
      return net::sizes::getVarSize((PRUint32)mUID)
           + net::sizes::getVarSize(mHealth)
           + net::sizes::getVarSize(mName)
           + net::sizes::getVarSize(mModel)
           + net::sizes::getVarSize((PRFloat64)mPosition[0]) * 3
           + net::sizes::getVarSize((PRFloat64)mVelocity[0]) * 3;
   }

   void Object::serialize(net::OutputStream& os) {
      os << mUID << mHealth << mName << mModel;
      for (unsigned int i=0; i<mPosition.Size; ++i) {
         os << (PRFloat64)mPosition[i];
      }
      for (unsigned int i=0; i<mVelocity.Size; ++i) {
         os << (PRFloat64)mVelocity[i];
      }
   }

   void Object::deserialize(net::InputStream& is) {
      is >> mUID >> mHealth >> mName >> mModel;
      for (int i=0; i<mPosition.Size; ++i) {
         PRFloat64 v;
         is >> v;
         mPosition[i] = v;
      }
      for (int i=0; i<mVelocity.Size; ++i) {
         PRFloat64 v;
         is >> v;
         mVelocity[i] = v;
      }
   }
}
