
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     gl render geoset     =-
//
// Description: "decoupled renderer for GeoSets"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: glRenderGeoSet.h,v $
//    $Date: 2001-09-20 20:12:50 $
//    $Revision: 1.7 $
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
#ifndef GLRENDERGEOSET_H_INCLUDED
#define GLRENDERGEOSET_H_INCLUDED

#include "GeoSet.h"
#include "glRenderTexture.h"

namespace kev
{
   inline void glRenderGeoSet( GeoSet& gset )
   {
      if (gset.gstate() != NULL)
      {
         kev::glRenderAndBind( gset.gstate()->texture );
      }
      
       float* data = NULL;
       int numVerts = 0;
   
       switch (gset.getPrimType())
       {
       case GeoSet::QUADS:
           data = gset.data();
           numVerts = gset.getNumVerts();
           glInterleavedArrays( GL_T2F_C4F_N3F_V3F, 0, data ); //GL_T2F_C4F_N3F_V3F            
           glDrawArrays( GL_QUADS, 0, numVerts );
           break;
       case GeoSet::TRIS:
           data = gset.data();
           numVerts = gset.getNumVerts();
           glInterleavedArrays( GL_T2F_C4F_N3F_V3F, 0, data ); //GL_T2F_C4F_N3F_V3F            
           glDrawArrays( GL_TRIANGLES, 0, numVerts );
           break;
       case GeoSet::TRISTRIPS:
           for (int x = 0; x < gset.getNumPrims(); ++x)
           {
               data = gset.data( x );
               numVerts = gset.getPrimLength( x );
               glInterleavedArrays( GL_T2F_C4F_N3F_V3F, 0, data ); //GL_T2F_C4F_N3$                
               glDrawArrays( GL_TRIANGLE_STRIP, 0, numVerts );
           }
           break;
       }
   }
   
   inline void glRenderGeoSets( std::vector<GeoSet*>& gsets )
   {
      for (int x = 0; x < gsets.size(); ++x)
      {
         glRenderGeoSet( *(gsets[x]) );
      }   
   }
}
#endif // ! GLRENDERGEOSET_H_INCLUDED
