#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include "Tank.h"
#include "Player.h"

//------------------------------------------------------------------------------

Player::Player()
   : mScore( 0L )
{
   mUID = UIDManager<Player>::instance().reserveID();
   mTank = new Tank();

   //init the camera
   mCamera.follow( true );
   mCamera.setTargetPos( mTank->matrix() );
   mCamera.setPitch( 30.0f );
}

//------------------------------------------------------------------------------

Player::~Player()
{
   UIDManager<Player>::instance().releaseID( mUID );
}

//------------------------------------------------------------------------------

const Player::UID&
Player::getUID() const
{
   return mUID;
}

//------------------------------------------------------------------------------

Tank*
Player::getTank()
{
   return mTank;
}

//------------------------------------------------------------------------------

const Tank*
Player::getTank() const
{
   return mTank;
}

//------------------------------------------------------------------------------

Camera&
Player::getCamera()
{
   return mCamera;
}

//------------------------------------------------------------------------------

const Camera&
Player::getCamera() const
{
   return mCamera;
}

//------------------------------------------------------------------------------

HUD&
Player::getHUD()
{
    return mHud;
}

//------------------------------------------------------------------------------

const HUD&
Player::getHUD() const
{
    return mHud;
}

//------------------------------------------------------------------------------

long
Player::getScore() const
{
   return mScore;
}

//------------------------------------------------------------------------------
