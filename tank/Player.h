#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "UIDManager.h"
//#include "Entity.h"
#include "Tank.h"
#include "Camera.h"
#include "HUD.h"

//: Describes a player that interacts with the environment. It is through the
//  player that you can gain access to that player's tank.
class Player
{
public:
   typedef UIDManager<Player>::UID UID;

public:
   Player();
   virtual ~Player();

   //: Get the unique ID associated with this player
   const UID& getUID() const;

   //: Gets the tank associated with this player
   Tank* getTank();
   const Tank* getTank() const;

   //: Gets the camera through which this player views the world
   Camera& getCamera();
   const Camera& getCamera() const;

   //: Gets the HUD for this player
   HUD& getHUD();
   const HUD& getHUD() const;

   //: Gets the player's current score
   long getScore() const;
private:
//   safe_ptr<Entity> mTank;
   Tank *mTank;

   //: Camera through which this player views the world
   Camera mCamera;

   //: Heads up display for text display
   HUD mHud;
   long mScore;
   UID mUID;
};

#endif // ! PLAYER_H_INCLUDED
