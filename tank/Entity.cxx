
#include "Entity.h"
#include "glRenderGeoSet.h"
#include "convert.h"

/*----------------------------------------------------------------------------*/

Entity::Entity()
   : mRot(), mBehavior(NULL)
{
}

/*----------------------------------------------------------------------------*/

Entity::~Entity()
{
   //Release our reference to the behavior object
   mBehavior->unref();

   //Release our reference to the geometry we used
   std::vector< safe_ptr<GeoSet> >::iterator itr;
   for (itr = mGeometry.begin; itr != mGeometry.end(); itr++) {
      (*itr)->unref();
   }
}

/*----------------------------------------------------------------------------*/

void
Entity::draw() const
{
    glPushMatrix();
        glMultMatrixf( mXForm.data() );
        
        std::vector< safe_ptr<GeoSet> >::const_iterator itr;
        for (itr = mGeometry.begin(); itr != mGeometry.end(); itr++) {
            glRenderGeoSet( *(*itr) );
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
Entity::addGeoSet(GeoSet *geoSet)
{
   mGeometry.push_back(geoSet);
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
