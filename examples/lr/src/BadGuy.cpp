#include <string>
#include <iostream>

#include "BadGuy.h"
#include "Level.h"
#include "Player.h"
#include "Texture.h"
#include "Types.h"


namespace lr
{
   BadGuy::BadGuy()
   {
   }

   void BadGuy::draw(){
      currentTexture->drawRectangle(realPos, realHeight+32, realPos+16, realHeight);
   }

   BadGuy::BadGuy(Level& theLevel, Player& thePlayer){
      mLevel = &theLevel;
      mPlayer = &thePlayer;
      realHeight = 768-64;
      realPos = 32;
      mTextureState = run1;

      // init all the keys to not down
      keyup = keydown = keyleft = keyright = false;

      // create the textures
      run1Image = Texture::create(std::string("lr-bg-1.png"));
      run2Image = Texture::create(std::string("lr-bg-2.png"));
      climb1Image = Texture::create(std::string("lr-bg-climb1.png"));
      climb2Image = Texture::create(std::string("lr-bg-climb2.png"));
      hang1Image = Texture::create(std::string("lr-bg-hang1.png"));
      hang2Image = Texture::create(std::string("lr-bg-hang2.png"));

      currentTexture = run1Image;
      initTime = 0.0;
   }

   void BadGuy::update(float dt)
   {
      textureState tempState;
      bool updateTex=false;
      // if it's not solid under us and we're not on a wire and we're not on a
      // ladder then we should be falling and if there is something solid under
      // us we still need to acutally fall all the way till we get to the bottom
      // of the block and we're not going off the screen
      if(!solidUnder() && !onWire() && !onLadder() || (solidUnder() && !onWire() && !onLadder() && (int)realHeight%32!=0) && realHeight>0) 
      {
         fall(dt);
      }
      else if(keyup && onLadder()) // we want to go up and we're on a ladder
      {
         realHeight+=((128*dt));
         tempState=climb1;
         updateTex=true;
      }
      else if(keydown && ((onLadder() || ladderUnder()) && (!brickUnder() || brickUnder() && (int)realHeight%32!=0)))
      // we want to go down and we're on a ladder and there is no brick under
      // us, or if there is we're not at the bottom of this block
      {
         realHeight-=((128*dt));
         tempState=climb1;
         updateTex=true;
      }
      else if(keydown && onWire() && !solidUnder() && !onLadder() && realHeight>0)
      // we want to fall if we're on a wire and there is nothing under us and
      // wer're not on a ladder
      {
         fall(dt);
      }
      else if(keyleft && (solidUnder() || onLadder()) && !brickLeft() && realPos>0) 
      // we want to go left and there is something under us there are no bricks
      // to our left and we aren't running off the screen
      {
         realPos-=((128*dt));
         tempState=run1;
         updateTex=true;
      }
      else if(keyright && (solidUnder() || onLadder()) && !brickRight() && realPos<1008)
      // we want to go right and there is something under us there are no bricks
      // to our right and we aren't running off the screen
      { 
         realPos+=((128*dt));
         tempState=run1;
         updateTex=true;
      }
      else if(keyleft && onWire() && !brickLeft() && realPos>0)
      // we want to go left and there is a wire there and there are no bricks to
      // our left and we are not running off the screen
      {
         realPos-=((128*dt));
         tempState=hang1;
         updateTex=true;
      }
      else if(keyright && onWire() && !brickRight() && realPos<1008)
      // we want to go right and there is a wire there and there are no bricks
      // to our right and we are not running off the screen
      {
         realPos+=((128*dt));
         tempState=hang1;
         updateTex=true;
      }

      if(isMoney())
      {
         mLevel->setEmpty(getGridPos(), getGridHeight());
      }

      std::cout << "fps: " << 1/dt << std::endl;
      if((initTime+=dt)>.08 && updateTex==true)
      {
         std::cout << "change texture" << std::endl;
         if(tempState==hang1)
         {
            std::cout << "hanging" << std::endl;
            if(mTextureState!=hang1){
               mTextureState=hang1;
               currentTexture = hang1Image;
            }else{
               mTextureState=hang2;
               currentTexture = hang2Image;
            }
         }else if(tempState==run1)
         {
            std::cout << "running" << std::endl;
            if(mTextureState!=run1){
               mTextureState=run1;
               currentTexture = run1Image;
            }else{
               mTextureState=run2;
               currentTexture = run2Image;
            }
         }else if(tempState==climb1)
         {
            std::cout << "climbing" << std::endl;
            if(mTextureState!=climb1){
               mTextureState=climb1;
               currentTexture = climb1Image;
            }else{
               mTextureState=climb2;
               currentTexture = climb2Image;
            }
         }
         initTime=0;
      }
      SDLKey temp;
      handleKeyPress(temp, true);

      
   }

   BadGuy::~BadGuy()
   {
   }

   bool BadGuy::ladderUnder()
   {
      if(mLevel->getEntityType(getGridPos(), (getGridHeight()-1)==ladder))
         return true;
      return false;
   }

   bool BadGuy::brickUnder()
   {
      if(mLevel->getEntityType(getGridPos(), (getGridHeight()-1))==brick)
         return true;
      return false;
   }
   
   bool BadGuy::solidUnder()
   {
      // if the block below us is a ladder or brick and we are at the bottom of
      // our current block then return true else return false
      if((mLevel->getEntityType(getGridPos(), (getGridHeight()-1))==brick) || (mLevel->getEntityType(getGridPos(), (getGridHeight()-1))==ladder) && (int)realHeight%32==0) 
         return true;
      if((mLevel->getEntityType(getGridPos(), (getGridHeight()-1))!=brick) && (mLevel->getEntityType(getGridPos(), (getGridHeight()-1)!=ladder) && (int)realHeight%32==0) && (int)realPos%16!=0)
         return true;
      if(realHeight<=0)
         return true;
      return false;
   }

   bool BadGuy::onWire()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==wire && (int)realHeight%32==0)
         return true;
      return false;
   }

   bool BadGuy::onLadder()
   {
      realPos+=8;
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
      {
         realPos-=8;
         return true;
      }
      realPos-=8;
      return false;
      
   }

   bool BadGuy::isMoney()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==money)
         return true;
      return false;
   }
         
   void BadGuy::setPos(int pos)
   {
      realPos = pos;
   }

   void BadGuy::setHeight(int h)
   {
      realHeight = h;
   }

   
   bool BadGuy::brickRight()
   {
      if((mLevel->getEntityType(getGridPos()+1, getGridHeight())==brick) && (int)realPos%32>=16)
         return true;
      if((int)realHeight%32>8 && (mLevel->getEntityType(getGridPos()+1, getGridHeight()+1)==brick) && (int)realPos%32<16)
         return true;
      return false;
   }

   bool BadGuy::brickLeft()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==brick)
         return true;
      return false;
   }

   /**
    * the handleKeyPress method for the badguys is where the ai happens.
    * Instead of having the ai controlling the location and direction of the 
    * badguy we have the ai decide which key's to press. 
    * NOTE:  we now call this method from badguys update method instead of 
    * getting called from the application since it would only get called on a
    * keypress that way.
    */
   void BadGuy::handleKeyPress(SDLKey sym, bool down)
   {
      // our (albeit stupid) ai works like this we see which directions the
      // player is from us (up,down,left,right) then we set those keys to be
      // true.
      if(mPlayer->getGridPos()>getGridPos()) // the player is right of us
      {
         keyright = true;
         keyleft = false;
      }else // the player is right of us 
      {
         keyleft = true;
         keyright = false;
      }
      if(mPlayer->getGridHeight()>getGridHeight()) // player is above us
      {
         keyup = true;
         keydown = false;
      }else // player is below us
      {
         keydown = true;
         keyup = false;
      }
      if(mPlayer->getGridHeight()==getGridHeight() && mPlayer->getGridPos()==getGridPos())
      {
         mLevel->readLevelFile(std::string("level1.lvl"), mPlayer, this);
         mPlayer->setLives(mPlayer->getLives()-1);
      }

   }
} // end namespace
