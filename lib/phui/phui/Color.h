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
 * File:          $RCSfile: Color.h,v $
 * Date modified: $Date: 2005-01-25 01:41:59 $
 * Version:       $Revision: 1.15 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_COLOR_H
#define PHUI_COLOR_H

#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>

namespace phui
{
   /**
    * Color tuple for easier color handling.
    */
   template< class TYPE >
   struct Color
   {
      /**
       * Creates a new uninitialized color.
       */
      Color() {}

      /**
       * Creates a color with the given color values.
       *
       * @param r_   the red part of the color
       * @param g_   the green part of the color
       * @param b_   the blue part of the color
       * @param a_   the alpha/transparent part of the color
       */
      Color(TYPE r_, TYPE g_, TYPE b_, TYPE a_)
         : r(r_), g(g_), b(b_), a(a_)
      {}

      /**
       * Changes this color to the new color values.
       *
       * @param r_   the red part of the color
       * @param g_   the green part of the color
       * @param b_   the blue part of the color
       * @param a_   the alpha/transparent part of the color
       */
      void set(TYPE r_, TYPE g_, TYPE b_, TYPE a_)
      {
         r = r_;
         g = g_;
         b = b_;
         a = a_;
      }

      TYPE r;  /**< The red part of the color. */
      TYPE g;  /**< The green part of the color. */
      TYPE b;  /**< The blue part of the color. */
      TYPE a;  /**< The alpha/transparent part of the color. */
   };
   // helper typedefs
   typedef Color<float>    Colorf;
   typedef Color<double>   Colord;
   typedef Color<int>      Colori;

   template< typename T >
   inline std::ostream& operator<<(std::ostream& out, const Color<T>& clr)
   {
      out<<"("<<clr.r<<", "<<clr.g<<", "<<clr.b<<", "<<clr.a<<")";
      return out;
   }

   template< typename T >
   inline bool operator==(const Color<T>& lhs, const Color<T>& rhs)
   {
      return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
   }

   template< typename T >
   inline bool operator!=(const Color<T>& lhs, const Color<T>& rhs)
   {
      return !(lhs == rhs);
   }

   //@{
   /**
    * OpenGL helper function to set our color struct as the current GL color.
    *
    * @param clr     the color to set as the current color
    */
   inline void glColor(const Colorf& clr)
   {
      glColor4f(clr.r, clr.g, clr.b, clr.a);
   }
   inline void glColor(const Colord& clr)
   {
      glColor4d(clr.r, clr.g, clr.b, clr.a);
   }
   inline void glColor(const Colori& clr)
   {
      glColor4i(clr.r, clr.g, clr.b, clr.a);
   }
   //@}

   static const Colorf NONE (0, 0, 0, 0);
   static const Colorf WHITE(1, 1, 1, 1);
   static const Colorf BLACK(0, 0, 0, 1);

   static const Colorf RED    (1, 0,    0, 1);
   static const Colorf ORANGE (1, 0.5,  0, 1);
   static const Colorf YELLOW (1, 1,    0, 1);
   static const Colorf GREEN  (0, 1,    0, 1);
   static const Colorf BLUE   (0, 0,    1, 1);
   static const Colorf PURPLE (1, 0,    1, 1);
}

#endif
