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
 * File:          $RCSfile: Stat.h,v $
 * Date modified: $Date: 2002-05-01 07:37:38 $
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
#ifndef DATA_STAT_H
#define DATA_STAT_H

#include <iostream>
#include <string>
#include <vector>

namespace data {

   ///A generalized statistic.
   class Stat {
   public:
      /// Creates a new stat with the given name/value.
      Stat(const std::string& name, const std::string& value)
         : mName(name), mValue(value)
      {}

      /// Gets the name of this stat.
      const std::string& getName() const {
         return mName;
      }
  
      /// Gets the value of this stat.
      const std::string& getVal() const {
         return mValue;
      }

      /// Sets the value of this stat.
      void setVal(const std::string& value) {
         mValue = value;
      }
  
      void xMLify(std::ostream& out) {
         out <<"        <stat name=\"" << mName << "\" value=\"" << mValue << "\" />" << std::endl;
      }

   private:
      /// The name of this stat.
      std::string mName;

      /// The value of this stat.
      std::string mValue;
   };

   typedef std::vector<Stat*> StatList;

}

#endif
