
#include "Entity.h"
#include "glRenderGeode.h"
#include "convert.h"

/*----------------------------------------------------------------------------*/

Entity::Entity()
   : mPos( 0,0,0 ), mRot(), mBehavior( NULL ), mGeometry( NULL )
{
}

/*----------------------------------------------------------------------------*/

void
Entity::draw() const
{
   glPushMatrix();
      glMultMatrixf( mXForm.data() );

      if ( mGeometry ) {
         kev::glRenderGeode( mGeometry );
      }
   glPopMatrix();
}

/*----------------------------------------------------------------------------*/

void
Entity::update( float timeDelta )
{
   kev::quat2mat( mPos, mRot, mXForm );
}

/*----------------------------------------------------------------------------*/

void
Entity::setPos(const Vec3f& pos)
{
   mPos = pos;
}

/*----------------------------------------------------------------------------*/

void
Entity::setRot(const Quat<float>& rot)
{
   mRot = rot;
}

/*----------------------------------------------------------------------------*/

void
Entity::translate( const Vec3f& offset )
{
   mPos += offset;
}

/*----------------------------------------------------------------------------*/

void
Entity::rotate( float deg, float x, float y, float z)
{
   mRot.makeRot( kev::deg2rad( deg ), x, y, z );
}

/*----------------------------------------------------------------------------*/

void
Entity::setGeode( Geode *geode)
{
   mGeometry = geode;
}

/*----------------------------------------------------------------------------*/

Geode*
Entity::getGeode()
{
   return mGeometry;
}

/*----------------------------------------------------------------------------*/

const Geode*
Entity::getGeode() const
{
   return mGeometry;
}

/*----------------------------------------------------------------------------*/

void
Entity::setBehavior(Behavior *behavior)
{
   mBehavior = behavior;
}
/*----------------------------------------------------------------------------*/

const Behavior*
Entity::behavior() const
{
   return (const Behavior *)mBehavior;
}

/*----------------------------------------------------------------------------*/

Vec3f
Entity::getForward() const
{
   Vec3f forward( 0,0,-1 );
   return mRot * forward;
}

/*----------------------------------------------------------------------------*/

const Matrix4f&
Entity::matrix() const
{
   return mXForm;
}

/*----------------------------------------------------------------------------*/

const Vec3f&
Entity::position() const
{
   return mPos;
}

/*----------------------------------------------------------------------------*/

const Quat<float>&
Entity::rotation() const
{
   return mRot;
}

/*----------------------------------------------------------------------------*/

const Entity::UID&
Entity::getUID() const
{
   return mUID;
}

/*----------------------------------------------------------------------------*/
