/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Color.h,v $
 * Date modified: $Date: 2002-02-24 05:33:08 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Ben Scott
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
 ************************************************************** phui-cpr-end */
#ifndef PHUI_COLOR_H
#define PHUI_COLOR_H

#include <GL/gl.h>

namespace phui {

   /**
    * Color tuple for easier color handling.
    */
   template< class TYPE >
   struct Color
   {
      TYPE r;
      TYPE g;
      TYPE b;
      TYPE a;
   };
   // helper typedefs
   typedef Color<float>    Colorf;
   typedef Color<double>   Colord;
   typedef Color<int>      Colori;
   typedef Color<long>     Colorl;

   //@{
   /**
    * OpenGL helper function to set our color struct as the current GL color.
    *
    * @param clr     the color to set as the current color
    */
   inline void glColor( const Colorf& clr )
   {
      glColor4f( clr.r, clr.g, clr.b, clr.a );
   }
   inline void glColor( const Colord& clr )
   {
      glColor4d( clr.r, clr.g, clr.b, clr.a );
   }
   inline void glColor( const Colori& clr )
   {
      glColor4i( clr.r, clr.g, clr.b, clr.a );
   }
   inline void glColor( const Colorl& clr )
   {
      glColor4l( clr.r, clr.g, clr.b, clr.a );
   }
   //@}

} // namespace phui

#endif
