/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: LayoutConstraint.h,v $
 * Date modified: $Date: 2003-01-05 13:21:33 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_LAYOUT_CONSTRAINT_H
#define PHUI_LAYOUT_CONSTRAINT_H

#include <string>
#include <boost/shared_ptr.hpp>

namespace phui
{
   /**
    * Represents a layout constraint.  This is used to create layout constraint
    * classes which can then be checked against by layout managers
    */
   class LayoutConstraint
   {
   public:
      virtual ~LayoutConstraint() {}
      /**
       * Gets the type of layout constraint represented by this class
       *
       * @return     the name of this layout constraint
       */
      virtual const std::string getType() = 0;
   };

   typedef boost::shared_ptr<LayoutConstraint> LayoutConstraintPtr;
}

#endif
