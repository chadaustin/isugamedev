#include <string>
#include <iostream>

#include "Player.h"
#include "Texture.h"
#include "Types.h"
#include "Level.h"

namespace lr
{

   void Player::draw(){
      currentTexture->drawRectangle(realPos, realHeight+32, realPos+16, realHeight);
   }

   Player::Player(Level& theLevel){
      mLevel = &theLevel;
      realHeight = 32;
      realPos = 0;
      mTextureState = run1;

      keyup = keydown = keyleft = keyright = false;

      // create the textures
      run1Image = Texture::create(std::string("lr1.png"));
      run2Image = Texture::create(std::string("lr2.png"));
      climb1Image = Texture::create(std::string("lr-climb1.png"));
      climb2Image = Texture::create(std::string("lr-climb2.png"));
      hang1Image = Texture::create(std::string("lr-hang1.png"));
      hang2Image = Texture::create(std::string("lr-hang2.png"));

      currentTexture = run1Image;
      initTime = 0.0;
   }


   void Player::update(float dt)
   {
      if(keyright==true && realPos<1008)
      {
         realPos++;
      }
      if(keyleft==true && realPos>0)
      {
         realPos--;
      }
      if((initTime+dt)>.08)
      {
         if(currentTexture == run1Image)
            currentTexture = run2Image;
         else
            currentTexture = run1Image;
         initTime=0;
      }else{
         initTime+=dt;
      }
   
   }

   Player::~Player()
   {
   }

   bool Player::brickUnder()
   {
      
      if(mLevel->getEntityType(getGridPos(), getGridHeight()-1)==brick)
         return true;
      return false;
   }

   bool Player::onWire()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==wire)
         return true;
      return false;
   }

   bool Player::onLadder()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
         return true;
      return false;
   }

   void Player::handleKeyPress(SDLKey sym, bool down)
   {
      if(sym == SDLK_DOWN && down)
      {
         keydown = true;
      }else if(sym == SDLK_UP && down)
      {
         keyup = true;
      }else if(sym == SDLK_LEFT && down)
      {
         keyleft = true;
      }else if(sym == SDLK_RIGHT && down)
      {
         keyright = true;
      }else if(sym == SDLK_DOWN && !down)
      {
         keydown = false;
      }else if(sym == SDLK_UP && !down)
      {
         keyup = false;
      }else if(sym == SDLK_LEFT && !down)
      {
         keyleft = false;
      }else if(sym == SDLK_RIGHT && !down)
      {
         keyright = false;
      }
   }

   
} // end namespace
