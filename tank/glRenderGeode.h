#ifndef GLRENDERGEODE_H_INCLUDED
#define GLRENDERGEODE_H_INCLUDED

#include <assert.h>
#include "Geode.h"
#include "glRenderGeoSet.h"

namespace kev
{
   //: Renders the given geode and all of its container geosets.
   inline void glRenderGeode( const GeodePtr geode )
   {
      assert( geode.get() && "glRenderGeode was given a NULL geode ptr" );
      glRenderGeoSets( geode->getGeoSets() );
   }
}

#endif // ! GLRENDERGEODE_H_INCLUDED
