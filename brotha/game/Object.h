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
 * File:          $RCSfile: Object.h,v $
 * Date modified: $Date: 2002-05-03 01:50:49 $
 * Version:       $Revision: 1.17 $
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
#ifndef OBJECT_H
#define OBJECT_H

#include "net/OutputStream.h"
#include "net/InputStream.h"
#include "net/Serialize.h"
#include "ObjectTypes.h"
#include "util/UIDManager.h"
#include <gmtl/Vec.h>
#include <gmtl/Sphere.h>

namespace game {
   class Object {
   public:
      /// UIDManager for objects
      typedef util::UIDManager<Object,PRUint32,1> UIDMgr;

      /// The UID type for objects.
      typedef UIDMgr::UID UID;

      /// The UID reserved for UNKNOWN players.
      static const UID UNKNOWN;

   public:
      Object();
      virtual ~Object();

      /**
       * Gets the unique ID associated with this object.
       */
      const UID& getUID() const;

      /**
       * Gets the unique name of this object.
       */
      const std::string& getName() const;

      /**
       * Gets the position vector associated with this object.
       */
      const gmtl::Point3f& getPosition() const {
         return mPosition;
      }

      /**
       * Sets the position vector associated with this object.
       */
      void setPosition(const gmtl::Point3f& pos) {
         mPosition = pos;
      }

      /**
       * Gets the velocity vector associated with this object.
       */
      const gmtl::Vec3f& getVelocity() const {
         return mVelocity;
      }

      /**
       * Sets the Velocity vector associated with this object.
       */
      void setVelocity(const gmtl::Vec3f& velocity) {
         mVelocity = velocity;
      }

      /**
       * Sets the Velocity vector associated with this object.
       */
      void setSphere(const gmtl::Spheref& sphere) {
         mSphere = sphere;
      }

      /**
       * Gets the velocity vector associated with this object.
       */
      const gmtl::Spheref& getSphere() const {
         return mSphere;
      }

      /**
       * Gets the health associated with this object.
       */
      const PRUint32 getHealth() const;

      /// Gets the name of the model for this object.
      const std::string& getModel() const;

      /// Sets the name of the model for this object.
      void setModel(const std::string& model);

      /**
       * Sets the position vector associated with this object.
       */
      void setHealth(PRUint32 health);

      virtual PRUint32 getType();
      virtual PRUint32 getSize();
      virtual void serialize(net::OutputStream& os);
      virtual void deserialize(net::InputStream& os);

   private:
      /// This object's UID
      UID mUID;

      /// The name of this object
      std::string mName;

      /// This object's position vector
      gmtl::Point3f mPosition;

      /// This object's velocity vector
      gmtl::Vec3f mVelocity;

      /// This object has a sphere surrounding it
      gmtl::Spheref mSphere;

      /// This object's health
      PRUint32 mHealth;

      /// The name of the model for this object.
      std::string mModel;
   };
}

#endif
