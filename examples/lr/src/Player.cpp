#include <string>
#include <iostream>

#include "Player.h"
#include "Texture.h"
#include "Types.h"
#include "Level.h"

namespace lr
{
   Player::Player()
   {
   }

   void Player::draw(){
      currentTexture->drawRectangle(realPos, realHeight+32, realPos+16, realHeight);
   }

   Player::Player(Level& theLevel){
      mLevel = &theLevel;
      realHeight = 32;
      realPos = 32;
      mTextureState = run1;

      // init all the keys to not down
      keyup = keydown = keyleft = keyright = burnright = burnleft = false;

      // create the textures
      run1Image = Texture::create(std::string("lr1.png"));
      run2Image = Texture::create(std::string("lr2.png"));
      climb1Image = Texture::create(std::string("lr-climb1.png"));
      climb2Image = Texture::create(std::string("lr-climb2.png"));
      hang1Image = Texture::create(std::string("lr-hang1.png"));
      hang2Image = Texture::create(std::string("lr-hang2.png"));

      currentTexture = run1Image;
      initTime = 0.0;

      // set lives to 1
      numLives = 3;

      // set the score to 0
      score = 0;

   }

   int Player::getLives()
   {
      return numLives;
   }

   int Player::getScore()
   {
      return score;
   }
   

   void Player::update(float dt)
   {
      if(dt>(1.0/128.0))
         dt=(1.0/32.0);
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
         score+=100;
      }

      if((initTime+=dt)>.08 && updateTex==true)
      {
         std::cout << "change texture" << std::endl;
         if(tempState==hang1)  // are we hanging
         {
            if(mTextureState!=hang1){
               mTextureState=hang1;
               currentTexture = hang1Image;
            }else{
               mTextureState=hang2;
               currentTexture = hang2Image;
            }
         }else if(tempState==run1)  // are we running
         {
            if(mTextureState!=run1){
               mTextureState=run1;
               currentTexture = run1Image;
            }else{
               mTextureState=run2;
               currentTexture = run2Image;
            }
         }else if(tempState==climb1) // are we climbing 
         {
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
      // if we are supposed to burn the right bricks out then do it
      if(burnright)
      {
         if((mLevel->getEntityType(getGridPos()+1,getGridHeight()-1)==brick) && (mLevel->getEntityType(getGridPos()+1,getGridHeight())!=brick)&& (mLevel->getEntityType(getGridPos()+1, getGridHeight())!=ladder))
            mLevel->burn(getGridPos()+1, getGridHeight()-1);

      }
      //if we are supposed to burn the left bricks out then do it
      if(burnleft)
      {
         if((mLevel->getEntityType(getGridPos()-1,getGridHeight()-1)==brick) && (mLevel->getEntityType(getGridPos()-1,getGridHeight())!=brick)&& (mLevel->getEntityType(getGridPos()-1, getGridHeight())!=ladder))
         mLevel->burn(getGridPos()-1, getGridHeight()-1);
      }
   }

   void Player::setPos(int pos)
   {
      realPos = pos;
   }

   void Player::setHeight(int h)
   {
      realHeight = h;
   }
   
   Player::~Player()
   {
   }

   bool Player::ladderUnder()
   {
      if(mLevel->getEntityType(getGridPos(), (getGridHeight()-1)==ladder))
         return true;
      return false;
   }

   bool Player::brickUnder()
   {
      if(mLevel->getEntityType(getGridPos(), (getGridHeight()-1))==brick)
         return true;
      return false;
   }
   
   bool Player::solidUnder()
   {
      std::cout << "player: " << (int)realHeight%32 << "  " << (int)realPos%16 << std::endl;
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

   bool Player::onWire()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==wire && (int)realHeight%32==0)
         return true;
      return false;
   }

   bool Player::onLadder()
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

   bool Player::isMoney()
   {
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==money)
         return true;
      return false;
   }
         

   bool Player::brickRight()
   {
      if((mLevel->getEntityType(getGridPos()+1, getGridHeight())==brick) && (int)realPos%32>=16)
         return true;
      if((int)realHeight%32>8 && (mLevel->getEntityType(getGridPos()+1, getGridHeight()+1)==brick) && (int)realPos%32<16)
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
      }else if(sym == SDLK_f && down)
      {
         burnright = true;
      }else if(sym == SDLK_f && !down)
      {
         burnright = false;
      }else if(sym == SDLK_d && down)
      {
         burnleft = true;
      }else if(sym == SDLK_d && !down)
      {
         burnleft = false;
      }
   }

   
} // end namespace
