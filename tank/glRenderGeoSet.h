#include "GeoSet.h"
#include "glRenderTexture.h"

void glRenderGeoSet( GeoSet& gset )
{
   if (gset.gstate() != NULL)
   {
      kev::glRenderBind( gset.gstate()->texture );
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

void glRenderGeoSets( std::vector<GeoSet*>& gsets )
{
   for (int x = 0; x < gsets.size(); ++x)
   {
      glRenderGeoSet( *(gsets[x]) );
   }   
}
