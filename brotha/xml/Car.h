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
 * Date modified: $Date: 2002-04-29 08:21:50 $
 * Version:       $Revision: 1.7 $
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

#include <iostream.h>
#include <string.h>
#include <vector>

#include "Cartype.h"
#include "BrothaData.h"
#include "Mod.h"

namespace data {
   class Car {
   private:
      modlist mods;

   public:
      std::string name;
      Car(std::string iname) {
         name = iname;
      }

      std::string getName() {
         return name;
      }

      modlist getMods() {
         return mods;
      }

      void addMod(Mod* m) {
         mods.push_back(m);
      }

      void xMLify(std::ostream& out) {
         out << "      <car cartype=\"" << name << "\">" << std::endl;
         for(unsigned int i = 0; i < mods.size(); ++i) {
            mods[i]->xMLify(out);
         }
         out << "      </car>" << std::endl;
      }
   };

   typedef std::vector<Car*> carlist;
}

#endif
