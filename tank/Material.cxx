
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     Material     =-
//
// Description: "Defines a material"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Material.cxx,v $
//    $Date: 2001-09-10 14:52:43 $
//    $Revision: 1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////

//////////////////////////////////////////////////////////////////////////////
#include <assert.h> // for assert
#include "Material.h"

Material::Material() : mAmbient( 0.0f, 0.0f, 0.0f, 1.0f ),
         mDiffuse( 0.3f, 0.3f, 0.3f, 1.0f ),
         mSpecular( 1.0f, 1.0f, 1.0f, 1.0f ),
         mShininess( 0.3f ),
         mEmissive( 0.0f, 0.0f, 0.0f, 1.0f )
{
}

// give - a number between [0,1] where 0 == no shine.
void Material::setShininess( const float& shine )
{
   assert( shine >= 0 && shine <= 1.0f && "argument not within bounds" );
   mShininess = shine;
}

// returns - a number between [0,1] where 0 == no shine.
void Material::getShininess( float& shine ) const
{
   shine = mShininess;
}

// give - a number between [0,1] where 0 == no transparency.
void Material::setTransparency( const float& trans )
{
   assert( trans >= 0 && trans <= 1.0f && "argument not within bounds" );
   
   //??? should all these be equal? or just the diffuse?
   mAmbient[3] = trans;
   mDiffuse[3] = trans;
   mSpecular[3] = trans;
}

// returns - a number between [0,1] where 0 == no transparency.
void Material::getTransparency( float& trans ) const
{
   //??? should all these be equal? or just the diffuse?
   trans = mAmbient[3];
}

// give - three numbers [r,g,b] between [0,1] where 0 is no color
void Material::setColor( Material::MaterialColorType which, float red, float green, float blue )
{
   switch (which)
   {
   case ambient:
      mAmbient[0] = red;
      mAmbient[1] = green;
      mAmbient[2] = blue;
      break;
   case diffuse:
      mDiffuse[0] = red;
      mDiffuse[1] = green;
      mDiffuse[2] = blue;
      break;
   case specular:  
      mSpecular[0] = red;
      mSpecular[1] = green;
      mSpecular[2] = blue; 
      break;
   case emissive:
      mEmissive[0] = red;
      mEmissive[1] = green;
      mEmissive[2] = blue;
      break;
   }
}

// give - three numbers [r,g,b] between [0,1] where 0 is no color
void Material::setColor( Material::MaterialColorType which, const float* const color )
{
   this->setColor( which, color[0], color[1], color[2] );
}

// returns - three numbers [r,g,b] between [0,1] where 0 is no color
void Material::getColor( Material::MaterialColorType which, float& red, float& green, float& blue ) const
{
   switch (which)
   {
   case ambient:
      red   = mAmbient[0];
      green = mAmbient[1];
      blue  = mAmbient[2];
      break;
   case diffuse:
      red   = mDiffuse[0];
      green = mDiffuse[1];
      blue  = mDiffuse[2];
      break;
   case specular:  
      red   = mSpecular[0];
      green = mSpecular[1];
      blue  = mSpecular[2];
      break;
   case emissive:
      red   = mEmissive[0];
      green = mEmissive[1];
      blue  = mEmissive[2];
      break;
   }
}

// returns - three numbers [r,g,b] between [0,1] where 0 is no color
void Material::getColor( Material::MaterialColorType which, float* color ) const
{
   this->getColor( which, color[0], color[1], color[2] );
}
