#include "RenderDynamicSystem.h"

template< class __Entity>
class glRenderEntityAsSphere : public RenderDynamicSystem<__Entity>::EntityRender
{
public:
   glRenderEntityAsSphere() {}
   virtual void render( const __Entity& p, bool useoffset, const Matrix4f& offset, int context = 0 ) const
   {
      float size = p.volume();
      float size_half = size * 0.5f;

      static GLUquadricObj* quad = ::gluNewQuadric(); 
   
      ::glPushMatrix();
         ::glTranslatef( p.position()[0],
                         p.position()[1],
                         p.position()[2] );
         ::glColor4fv( p.color().data() );
         ::gluSphere( quad, size_half, 3, 3 );
      ::glPopMatrix();
   }
};

#include "Fizix/example/cubeGeometry.h"
template< class __Entity>
class glRenderEntityAsCube : public RenderDynamicSystem<__Entity>::EntityRender
{
public:
      cubeGeometry cg;
   virtual void render( const __Entity& p, bool useoffset, const Matrix4f& offset, int context = 0 ) const
   {
      ::glPushAttrib( GL_ENABLE );
      ::glDisable( GL_TEXTURE_2D );
      ::glPushMatrix();
         ::glTranslatef( p.position()[0],
		      p.position()[1],
		      p.position()[2] );
         ::glColor4fv( p.color().data() );
         
         cg.render();
         
      ::glPopMatrix();
      ::glPopAttrib();
   }
};


#include "Matrix4f.h"
#include "Quat.h"
#include "glRenderTexture.h"
#include "glRenderMaterial.h"
#include "ImageManager.h"

#include "GeodeCache.h"
#include "glRenderGeode.h"
#include "convert.h"


// particle render functor for the Sprite particle system renderer
template< class __Entity>
class glRenderEntityAsGeom : public RenderDynamicSystem<__Entity>::EntityRender
{
public:
   cubeGeometry cg;
   virtual void render( const __Entity& p, bool useoffset, const Matrix4f& offset, int context = 0 ) const
   {
      ::glPushMatrix();
      ::glTranslatef( p.position()[0],
                      p.position()[1],
                      p.position()[2] );
      if (useoffset)
      {
         ::glMultMatrixf( offset.data() );
      }

//      cg.render();      
      kev::glRenderGeode( mGeometry );
      
      ::glPopMatrix();
   }

   void setGeom( const std::string& filename )
   {
      GeodeCache::instance().load( mGeometry, filename );
   }
private:
   GeodePtr mGeometry;
};
