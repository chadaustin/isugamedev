
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     gl render material     =-
//
// Description: "decoupled renderer for Materials"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: glRenderMaterial.h,v $
//    $Date: 2001-09-20 20:12:50 $
//    $Revision: 1.2 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
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
#ifndef GLRENDER___MATERIAL
#define GLRENDER___MATERIAL


#include "Material.h"

namespace kev
{

   inline void glRender( const Material& material )
   {
      float shininess;
      material.getShininess( shininess );
      shininess *= 128.0f;
      
      float ambient[3], diffuse[3], specular[3], emissive[3];

      material.getColor( Material::ambient, ambient );
      material.getColor( Material::diffuse, diffuse );
      material.getColor( Material::specular, specular );
      material.getColor( Material::emissive, emissive );

      // TODO: add the capability for front, or back, or both...
      glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
      glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
      glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
      glMaterialfv( GL_FRONT, GL_EMISSION, emissive );
      glMaterialfv( GL_FRONT, GL_SHININESS, &shininess );
   }

};

#endif
