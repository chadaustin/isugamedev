
#include "Entity.h"
#include "glRenderGeode.h"
#include "convert.h"

/*----------------------------------------------------------------------------*/

Entity::Entity()
   : mGeometry( NULL )
{
}

/*----------------------------------------------------------------------------*/

void
Entity::draw() const
{
   glPushMatrix();
      glMultMatrixf( mXForm.data() );

      if ( mGeometry.get() != NULL ) {
         kev::glRenderGeode( mGeometry );
      }
   glPopMatrix();
}

/*----------------------------------------------------------------------------*/

void
Entity::update( float timeDelta )
{
   kev::quat2mat( mPosition, mRotation, mXForm );
}

/*----------------------------------------------------------------------------*/

void
Entity::translate( const Vec3f& offset )
{
   mPosition += offset;
}

/*----------------------------------------------------------------------------*/

void
Entity::rotate( float deg, float x, float y, float z)
{
   mRotation.makeRot( kev::deg2rad( deg ), x, y, z );
}

/*----------------------------------------------------------------------------*/

void
Entity::setGeode( GeodePtr geode)
{
   mGeometry = geode;
}

/*----------------------------------------------------------------------------*/

GeodePtr
Entity::getGeode()
{
   return mGeometry;
}

/*----------------------------------------------------------------------------*/

const GeodePtr
Entity::getGeode() const
{
   return mGeometry;
}

/*----------------------------------------------------------------------------*/

Vec3f
Entity::getForward() const
{
   Vec3f forward( 0,0,-1 );
   return mRotation * forward;
}

/*----------------------------------------------------------------------------*/

const Matrix4f&
Entity::matrix() const
{
   return mXForm;
}

/*----------------------------------------------------------------------------*/

const Entity::UID&
Entity::getUID() const
{
   return mUID;
}

/*----------------------------------------------------------------------------*/
