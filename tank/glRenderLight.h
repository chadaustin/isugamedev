
//////////////////////////////////////////////////////////////////////////////
//
//                         -= glRenderLight =-
//
// Description: "Light renderer for OGL"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: glRenderLight.h,v $
//    $Date: 2001-09-10 16:25:10 $
//    $Revision: 1.5 $
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
#ifndef GLRENDERLIGHT_H_INCLUDED
#define GLRENDERLIGHT_H_INCLUDED

#include <assert.h>

#ifdef WIN32
   #include <windows.h>
#endif
#include <GL/gl.h>    //for opengl
#include <GL/glu.h>   //for opengl utility

#include "Light.h"

namespace kev
{
   
   void glRender( const Light& light )
   {
       int lightNumber = GL_LIGHT0;

       // figure out which GL light number the light is...
       switch (light.number())
       {
       case 0: lightNumber = GL_LIGHT0; break;
       case 1: lightNumber = GL_LIGHT1; break;
       case 2: lightNumber = GL_LIGHT2; break;
       case 3: lightNumber = GL_LIGHT3; break;
       case 4: lightNumber = GL_LIGHT4; break;
       case 5: lightNumber = GL_LIGHT5; break;
       case 6: lightNumber = GL_LIGHT6; break;
       case 7: lightNumber = GL_LIGHT7; break;
       default:
	   // light number has to be in the range [0,7] 
	   // when rendering with OpenGL.
	   std::cout<<"light number "<<light.number()<<" has to be in the range [0,7]\n"<<std::flush;
	   assert(light.number()>=0 && light.number()<=7);
	   lightNumber = GL_LIGHT0; break;
       }

       if (light.isOn())
      {
          // gather the data to be used to setup the opengl light.
          float ambient[3], diffuse[3], specular[3], position[4];
          float constantAttenuation, linearAttenuation, quadraticAttenuation;
          float cutoff, direction[3], exponent;
          light.getColor( Light::ambient, ambient[0], ambient[1], ambient[2] );
          light.getColor( Light::diffuse, diffuse[0], diffuse[1], diffuse[2] );
          light.getColor( Light::specular, specular[0], specular[1], specular[2] );
          light.getPos( position[0], position[1], position[2], position[3] );
          light.getAtten( constantAttenuation, linearAttenuation, quadraticAttenuation );
          light.getSpotDir( direction[0], direction[1], direction[2] );
          light.getSpotCone( exponent, cutoff );

          // light color.
          glLightfv(lightNumber, GL_AMBIENT, ambient);
          glLightfv(lightNumber, GL_DIFFUSE, diffuse);
          glLightfv(lightNumber, GL_SPECULAR, specular);

          // position
          glLightfv(lightNumber, GL_POSITION, position);

          // attenuation
          glLightfv(lightNumber, GL_CONSTANT_ATTENUATION, &constantAttenuation);
          glLightfv(lightNumber, GL_LINEAR_ATTENUATION, &linearAttenuation);
          glLightfv(lightNumber, GL_QUADRATIC_ATTENUATION, &quadraticAttenuation);

          // spotlight
          glLightfv( lightNumber, GL_SPOT_CUTOFF, &cutoff );
          glLightfv( lightNumber, GL_SPOT_DIRECTION, direction );
          glLightfv( lightNumber, GL_SPOT_EXPONENT, &exponent );

          glEnable( lightNumber );

          const float thisIsFalse[] = { GL_FALSE };
          //const float thisIsTrue[] = { GL_TRUE };
          glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, thisIsFalse);
          glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, thisIsFalse);
          glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
      }
      else
      {
          glDisable( lightNumber );
      }
   }

};


#endif // ! GLRENDERLIGHT_H_INCLUDED
