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
 * File:          $RCSfile: ModType.h,v $
 * Date modified: $Date: 2002-05-01 21:46:09 $
 * Version:       $Revision: 1.1 $
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
#ifndef DATA_MODTYPE_H
#define DATA_MODTYPE_H

#include <iostream>
#include <string>
#include <vector>

namespace data {

   class ModType {


   public:
      /// Create a new cartype with the given name and model.
	   ModType(const std::string& name, int min, int max){
		   mName = name;
		   mn = min;
		   mx = max;
       }



      /// Gets the name of this car type.
      const std::string& getName() const {
         return mName;
      }

	  int getMin(){
		  return mn;
	  }
	  int getMax(){
		  return mx;
	  }


      void xMLify(std::ostream& out) {
         out << "  <modtype name=\"" << mName << "\" min=\"" << mn<< "\" max=\"" <<mx <<"\" />" << std::endl;
      }

   private:
	   std::string mName;
	   int mn,mx;
   };

   typedef std::vector<ModType*> ModTypeList;

}
#endif
