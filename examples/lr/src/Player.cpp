#include "Player.h"
#include "Texture.h"
#include "Types.h"

namespace lr
{

   void Player::draw(){

   }

   Player::Player(Level& theLevel){
      mLevel = &theLevel;
      realHeight = 32;
      realPos = 0;
      mTextureState = run1;
   }


   void Player::update(float dt)
   {
   }

   Player::~Player()
   {
   }

} // end namespace
