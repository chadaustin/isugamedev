
//////////////////////////////////////////////////////////////////////////////
//
//                   -=    Material    =-
//
// Description: "Defines a material"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//   $RCSfile: Material.h,v $
//   $Date: 2001-09-10 14:52:43 $
//   $Revision: 1.1 $
//   Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
//
//   This library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Library General Public
//   License as published by the Free Software Foundation; either
//   version 2 of the License, or (at your option) any later version.
//
//   This library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Library General Public License for more details.
//
//   You should have received a copy of the GNU Library General Public
//   License along with this library; if not, write to the Free
//   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////

//////////////////////////////////////////////////////////////////////////////
#ifndef MATERIAL_INCLUDED
#define MATERIAL_INCLUDED

#include "ColorRGBA.h"
class Material
{
// Construction:
public:
   //: constructor
   Material();

   enum MaterialColorType
   {
      ambient, diffuse, specular, emissive
   };

// Methods:
public:
   // give a number between [0,1] where 0 == no shine.
   void setShininess( const float& shine );

   // returns - a number between [0,1] where 0 == no shine.
   void getShininess( float& shine ) const;
   
   
   // give a number between [0,1] where 0 == no transparency.
   void setTransparency( const float& trans );

   // returns - a number between [0,1] where 0 == no transparency.
   void getTransparency( float& trans ) const;

      
   // set material color
   // give three numbers [r,g,b] between [0,1] where 0 is no color
   void setColor( MaterialColorType which, float red, float green, float blue );
   
   // set material color
   // give three numbers [r,g,b] between [0,1] where 0 is no color
   void setColor( MaterialColorType which, const float* const color );

   // returns - three numbers [r,g,b] between [0,1] where 0 is no color
   void getColor( MaterialColorType which, float* ambient ) const;

   // returns - three numbers [r,g,b] between [0,1] where 0 is no color
   void getColor( MaterialColorType which, float& red, float& green, float& blue ) const;

protected:
   float       mShininess;
   ColorRGBA   mAmbient; 
   ColorRGBA   mDiffuse;
   ColorRGBA   mSpecular;
   ColorRGBA   mEmissive;
   
   // TODO: add the flag for front, or back, or both sides...
};

#endif
