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
