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
 * File:          $RCSfile: CarType.h,v $
 * Date modified: $Date: 2002-04-29 07:41:39 $
 * Version:       $Revision: 1.4 $
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
#ifndef DATA_CARTYPE_H
#define DATA_CARTYPE_H

#include <iostream>
#include <string>
#include <vector>

namespace data {

   class Cartype {
   private:
      std::string name;
      std::string filename;

   public:
      Cartype() {
         name = "none!";
         filename = "car.model";
      }

      Cartype(std::string iname) {
         name = iname;
         filename = "car.model";
      }

      Cartype(std::string in_name, std::string imodl) {
         name = in_name;
         filename = imodl;
      }

      std::string getFileName() {
         return filename;
      }

      std::string getName() {
         return name;
      }

      void xMLify(std::ostream& out) {
         out << "  <cartype name=\"" << name << "\" file=\"" << filename<< "\" />" << std::endl;
      }
   };

   typedef std::vector<Cartype*> cartypelist;

}
#endif
