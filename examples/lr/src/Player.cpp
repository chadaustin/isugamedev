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
      realPos = 32;
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
      if((!brickUnder() && !ladderUnder() && !onWire() && !onLadder()))
      {
         fall();
         std::cout << "1" << std::endl;
      }
      else if(keyup && onLadder())
      {
         realHeight++;
         std::cout << "2" << std::endl;
      }
      else if(keydown && (onLadder() || ladderUnder()))
      {
         if((int)realHeight%32==0 && brickUnder())
         {
            // special case when for when we hit the bottom of the ladder - do
            // nothing
         }else
         {
            realHeight--;
         }
   
         std::cout << "3" << std::endl;
      }
      else if(keydown && onLadder() && brickUnder())  // special case if we're on the ladder just above some brick then we need to only go as far as the brick.
      {
         if((int)realPos%32!=0)
            realHeight--;
         
      }
      else if(keydown && onWire() && !brickUnder() && !ladderUnder() && !onLadder())
      {
         fall();
         std::cout << "4" << std::endl;
      }
      else if(keyleft && (brickUnder() || ladderUnder()) && !brickLeft() && realPos>0)
      {
         realPos--;
         std::cout << "5" << std::endl;
      }
      else if(keyright && (brickUnder() || ladderUnder()) && !brickRight() && realPos<1008)
      { 
         realPos++;
         std::cout << "6" << std::endl;
      }
      else if(keyleft && onWire() && !brickLeft() && realPos>0)
      {
         realPos--;
         std::cout << "7" << std::endl;
      }
      else if(keyright && onWire() && !brickRight() && realPos<1008)
      {
         realPos++;
         std::cout << "8" << std::endl;
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

   bool Player::ladderUnder()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight()-1)==ladder)
         return true;
      return false;
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

   bool Player::brickRight()
   {
      if((mLevel->getEntityType(getGridPos()+1, getGridHeight())==brick) && (int)realPos%32<16)
         return true;
      return false;
   }

   bool Player::brickLeft()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==brick)
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
