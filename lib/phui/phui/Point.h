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
 * File:          $RCSfile: Point.h,v $
 * Date modified: $Date: 2005-01-25 01:42:05 $
 * Version:       $Revision: 1.14 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_POINT_H
#define PHUI_POINT_H

#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>
#include <iostream>

namespace phui
{
   class Point
   {
   public:
      Point()               { x = 0;   y = 0; }
      Point(int x_, int y_) { x = x_ ; y = y_; }
      Point(const Point& p) { x = p.x; y = p.y; }

      void set(int x_, int y_)
      {
         x = x_;
         y = y_;
      }

      int x;
      int y;

      Point& operator+=(const Point& p)
      {
         x += p.x;
         y += p.y;
         return *this;
      }

      Point& operator-=(const Point& p)
      {
         x -= p.x;
         y -= p.y;
         return *this;
      }
   };


   inline Point operator-(const Point& lhs, const Point& rhs)
   {
      return Point(lhs.x - rhs.x, lhs.y - rhs.y);
   }

   inline Point operator+(const Point& lhs, const Point& rhs)
   {
      return Point(lhs.x + rhs.x, lhs.y + rhs.y);
   }

   inline bool operator==(const Point& lhs, const Point& rhs)
   {
      return (lhs.x == rhs.x && lhs.y == rhs.y);
   }

   inline bool operator!=(const Point& lhs, const Point& rhs)
   {
      return !(lhs == rhs);
   }

   inline std::ostream& operator<<(std::ostream& os, const Point& p)
   {
      os << "(" << p.x << ", " << p.y << ")";
      return os;
   }

   inline void glVertex(const Point& p)
   {
      glVertex2i(p.x, p.y);
   }
}

#endif
