#include <assert.h>
#include <Quat.h>
#include <Matrix4f.h>
#include <Vec3.h>
#include <Defines.h>

#include "QuakeNav.h"  // My Header

QuakeNav::QuakeNav() :
                       eye( 0, 0, 0 ), 
                       up( 0, 1, 0 ), 
                       direction( 0, 0, -1 ), pitch( 0 ), yaw( 0 ),
                       mLookAtMatrix( Matrix4f::identity() )
{
}

void QuakeNav::applyYtrans( const float& delta )
{
   if (delta != 0.0f)
   {
      eye += up * (-delta);
      _recalcMatrix();
   }
}

void QuakeNav::applyXtrans( const float& delta )
{
   if (delta != 0.0f)
   {
      //(slide horizontally in user's local coordinate system)
      Vec3<float> localXaxis = up.cross( direction );
      eye += localXaxis * (-delta);
    
      _recalcMatrix();
   }
}

void QuakeNav::applyZtrans( const float& delta )
{
   if (delta != 0.0f)
   {
      //go forward with respect to your view.
      eye += direction * (-delta);

      _recalcMatrix();
   }
}

void QuakeNav::applyXYtrans( const float& xdelta, const float& ydelta )
{
    applyXtrans( xdelta );
    applyYtrans( ydelta );
}

//strafe in the XZ plane
void QuakeNav::applyXZtrans( const float& xdelta, const float& ydelta )
{
    applyXtrans( xdelta );
    applyZtrans( ydelta );
}

void QuakeNav::applyXrot( const float& delta )
{
    //Pitch
    if ( delta != 0.0f )
    {
      pitch += kev::deg2rad( delta );
      if (pitch > kev::deg2rad( 90.0f ) ) 
         pitch = kev::deg2rad( 90.0f );
      if (pitch < kev::deg2rad( -90.0f) ) 
         pitch = kev::deg2rad( -90.0f );
      _recalcMatrix();
    }
}

void QuakeNav::applyYrot( const float& delta )
{
    //Pitch
    if ( delta != 0.0f )
    {
      yaw += kev::deg2rad( delta );
      _recalcMatrix();
    }
}

void QuakeNav::applyZrot( const float& delta )
{
    assert( false && "not implemented" );
}

void QuakeNav::applyGeneralRot( const float& xdelta, const float& ydelta )
{
   applyYrot( xdelta );
   applyXrot( ydelta );
}
