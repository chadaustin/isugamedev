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
 * File:          $RCSfile: Mod.h,v $
 * Date modified: $Date: 2002-05-01 07:16:59 $
 * Version:       $Revision: 1.6 $
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
#ifndef DATA_MOD_H
#define DATA_MOD_H

#include <iostream>
#include <string>
#include <vector>

namespace data {

   /**
    * A particular modification to a car.
    */
   class Mod {
   public:
      /**
       * Creates a new mod with the given name and level.
       */
      Mod(const std::string& name, int level) {
         mName = name;
         mLevel = level;
      }

      /**
       * Returns the name of the mod.
       */
      const std::string& getName() const {
         return mName;
      }
  
      /**
       * Returns the level of the mod
       */
      int getLevel() const {
         return mLevel;
      }
  
      void xMLify(std::ostream& out) {
         out <<"        <mod name=\"" << mName << "\" level=\"" << mLevel << "\" />" << std::endl;
      }

   private:
      /// Type of mod
      std::string mName;

      /// Level of Mod
      int mLevel;
   };

   typedef std::vector<Mod*> ModList;
}

#endif
