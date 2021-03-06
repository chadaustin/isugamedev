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
 * File:          $RCSfile: Car.h,v $
 * Date modified: $Date: 2002-05-03 09:52:06 $
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
#ifndef DATA_CAR_H
#define DATA_CAR_H

#include <iostream>
#include <string.h>
#include <vector>

#include "CarType.h"
#include "Mod.h"

namespace data {
   class Car {
   public:

  	   std::string mPic; //image URL
	   std::string mThumbPic; //thumbnail image url
      /// Creates a new car with the given name.
      Car(const std::string& name) {
         mName = name;
         mPic = std::string("");
         mThumbPic = std::string("");
      }

      /// Gets the name of this car.
      const std::string& getName() const {
         return mName;
      }

      /// Gets a list of the mods on this car
      ModList& getMods() {
         return mMods;
      }

      /// Adds the given mod to this car.
      void addMod(Mod* m) {
         mMods.push_back(m);
      }

      void removeMod(std::string name){
	      for(unsigned int i = 0; i < mMods.size(); i++){
		      Mod* c = mMods[i];
		      if(name == c->getName()){
			      mMods.erase(mMods.begin() + i);
		      }
	      }
      }

      Mod* getMod(std::string name) {
         for(unsigned int x=0;x<mMods.size();++x) {
            Mod* c = mMods[x];
            if(name == c->getName()) {
               return c;
            }
         }

         return NULL;
      }

      void xMLify(std::ostream& out) {
         out << "      <car cartype=\"" << mName << "\" pic=\"" << mPic << "\" lilpic=\"" << mThumbPic << "\" >" << std::endl;
         for(unsigned int i = 0; i < mMods.size(); ++i) {
            mMods[i]->xMLify(out);
         }
         out << "      </car>" << std::endl;
      }


   private:
      /// The name of this car.
      std::string mName;

      /// The mods on this car.
      ModList mMods;
   };

   typedef std::vector<Car*> CarList;
}

#endif
