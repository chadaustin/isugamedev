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
      if(!mPlayer->amDead())
      currentTexture->drawRectangle(realPos, realHeight+32, realPos+16, realHeight);
   }

   BadGuy::BadGuy(Level& theLevel, Player& thePlayer){
      mLevel = &theLevel;
      mPlayer = &thePlayer;
      realHeight = 768-64;
      realPos = 32;
      mTextureState = runright1;

      // init all the keys to not down
      keyup = keydown = keyleft = keyright = false;

      // create the textures
      run1leftImage = Texture::create(std::string("lr1-bg-left.png"));
      run2leftImage = Texture::create(std::string("lr2-bg-left.png"));
      run3leftImage = Texture::create(std::string("lr3-bg-left.png"));
      run1rightImage = Texture::create(std::string("lr1-bg-right.png"));
      run2rightImage = Texture::create(std::string("lr2-bg-right.png"));
      run3rightImage = Texture::create(std::string("lr3-bg-right.png"));
      climb1Image = Texture::create(std::string("lr-bg-climb1.png"));
      climb2Image = Texture::create(std::string("lr-bg-climb2.png"));
      hang1leftImage = Texture::create(std::string("lr-bg-hang1-left.png"));
      hang2leftImage = Texture::create(std::string("lr-bg-hang2-left.png"));
      hang3leftImage = Texture::create(std::string("lr-bg-hang3-left.png"));
      hang1rightImage = Texture::create(std::string("lr-bg-hang1-right.png"));
      hang2rightImage = Texture::create(std::string("lr-bg-hang2-right.png"));
      hang3rightImage = Texture::create(std::string("lr-bg-hang3-right.png"));

      currentTexture = run1rightImage;
      initTime = 0.0;

      atGoal=true;
      goal = new Block(0,0);
   }

   void BadGuy::fall(float dt)
   {
      float beforeHeight=realHeight;
      float remainingHeight;
      realHeight-=(128*dt);
      // if we have fallen through bricks then we need to bring us back up here
      if(((int)realHeight%32)>((int)beforeHeight%32) && (int)beforeHeight%32!=0)
      {
         remainingHeight=(int)beforeHeight%32;
         realHeight=beforeHeight-remainingHeight;
      }
      atGoal=true;
   }

   playerRelativePos BadGuy::getRelativeDirection()
   {
      if(abs(mPlayer->getGridHeight()-getGridHeight()) < abs(mPlayer->getGridPos()-getGridPos()))
      { // then we are closer horizontally then vertically
         if(mPlayer->getGridPos()<getGridPos())
         { // then the player is left of us
            if(mPlayer->getGridHeight()>getGridHeight())
            { // then the player is above us
               return leftup;
            }else
            { // the player is below us
               return leftdown;
            }
         }else
         { // then the player is right of us
            if(mPlayer->getGridHeight()>getGridHeight())
            {
               return rightup;
            }else
            { // hte player is below us
               return rightdown;
            }
         }
      }else
      { // then we are closer vertically then horizontally
         if(mPlayer->getGridPos()<getGridPos())
         { // then the player is left of us
            if(mPlayer->getGridHeight()>getGridHeight())
            { // then the player is above us
               return upleft;
            }else
            { // the player is below us
               return downleft;
            }
         }else
         { // then the player is right of us
            if(mPlayer->getGridHeight()>getGridHeight())
            {
               return upright;
            }else
            { // hte player is below us
               return downright;
            }
         }
      }
   }
               
         
   
   void BadGuy::chooseNextGoal()
   {
      atGoal=false;
      if(getRelativeDirection()==upright) 
      { // then the player is closer up and also to the right
         // first check if we are at a ladder and if we are then go up
         std::cout << "upright" << std::endl;
         if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
         {
            std::cout << "we're at a ladder" << std::endl;
            // then set the goal at teh end of the ladder or at the height
            // of the player whichever is first
            // found is for the case that we find the node
            int i=0;
            for(i=getGridHeight();mLevel->getEntityType(getGridPos(), i)==ladder;i++)
            {
            }
            if(mLevel->getEntityType(getGridPos(),i)==empty)
            {
               std::cout << "empty i: " << i << std::endl;
               // now set the goal at the end of the ladder   
               goal->pos=getGridPos();
               goal->height=i;
            }
            else
            {

               std::cout << "not empty i: " << i << std::endl;
               goal->pos=getGridPos();
               goal->height=i-1;
            }
         }
         else
         { // we are not at a ladder
         
            // so find a ladder and set that position as our goal location
            bool found=false;
            for(int i=getGridPos()+1;i<32 && !found;i++)
            {
               // if we find a ladder to our right
               if(mLevel->getEntityType(i,getGridHeight()) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
               // or if we find a brick in our path then we are screwed 
               if(mLevel->getEntityType(i,getGridHeight()) == brick)
               {
                  found=false;
                  i=32;
               }
            }
            if(!found) // then we didn't find a ladder so look left
            {
               for(int i=getGridPos();i>0;i--)
               {
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
                  if(mLevel->getEntityType(i,getGridHeight()) == brick)
                  {
                     found=false;
                     i=32;
                  }
               }
            }
         }
         std::cout << "playerPos: " << getGridPos() << "," << getGridHeight() << std::endl;
         std::cout << "goal  Pos: " << goal->pos << "," << goal->height << std::endl;
      }else if(getRelativeDirection()==rightup)
      { // then the player is closer right and also above us
         // first check if we are at aladder and if we are then go up
         // now check if we are already at a ladder
         std::cout << "rightup" << std::endl;
         if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
         {
            // then set the goal at teh end of the ladder or at the height
            // of the player whichever is first
            // found is for the case that we find the node
            int i=0;
            for(i=getGridHeight();mLevel->getEntityType(getGridPos(), i)==ladder;i++)
            {
            }
            if(mLevel->getEntityType(getGridPos(),i)==empty)
            {
               // now set the goal at the end of the ladder   
               goal->pos=getGridPos();
               goal->height=i;
            }
            else
            {
               goal->pos=getGridPos();
               goal->height=i-1;
            }
         }
         else
         {
            // so find a ladder and set that position as our goal location
            bool found=false;
            for(int i=getGridPos()+1;i<32 && !found;i++)
            {
               // if we find a ladder to our right
               if(mLevel->getEntityType(i,getGridHeight()) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
            if(!found) // then we didn't find a ladder so look left
            {
               for(int i=getGridPos();i>0;i--)
               {
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
            }
         }
      }else if(getRelativeDirection()==downright)
      { // the the player is closer below us and also to our right
         // so check if we are at a ladder
        // if the player is below usp
         std::cout << "downright" << std::endl;
         // then check if we are at a ladder to take us down
         if(mLevel->getEntityType(getGridPos(),getGridHeight()-1)==ladder)
         {
            // then set the goal at the end of the ladder or at the height
            // of the player whichever is first
            // found is for the case that we find the node
            int i;
            for(i=getGridHeight()-1;mLevel->getEntityType(getGridPos(),i)==ladder;i--)
            {
            }
            // now set the goal pos at the end of the ladder
            goal->pos=getGridPos();
            goal->height=i+1;
            
         } else
         {  // we weren't at a ladder so look for one first to our right then 
            //to our left
            bool found=false;
            for(int i=getGridPos()+1;i<32 && !found;i++)
            {
               // if we find a ladder to our right
               if(mLevel->getEntityType(i,getGridHeight()) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
            if(!found) // then we didn't find a ladder so look left
            {
               for(int i=getGridPos();i>0;i--)
               {
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
            }
         }
      }else if(getRelativeDirection()==rightdown)
      { // the player is closer right of us and also down from us
         // so find a ladder and set that position as our goal location
         std::cout << "rightdown" << std::endl;
         bool found=false;
         for(int i=getGridPos()+1;i<32 && !found;i++)
         {
            // if we find a ladder to our right
            if(mLevel->getEntityType(i,getGridHeight()-1) == ladder)
            {
               found=true;
               goal->pos=i;
               goal->height=getGridHeight();
            }
         }
         if(!found) // then we didn't find a ladder so look left
         {
            for(int i=getGridPos();i>0;i--)
            {
               if(mLevel->getEntityType(i,getGridHeight()-1) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
         }
      }else if(getRelativeDirection()==upleft) 
      { // then the player is closer up and also to the left
         // first check if we are at a ladder and if we are then go up
         std::cout << "upleft" << std::endl;
         if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
         {
            // then set the goal at teh end of the ladder or at the height
            // of the player whichever is first
            // found is for the case that we find the node
            int i=0;
            for(i=getGridHeight();mLevel->getEntityType(getGridPos(), i)==ladder;i++)
            {
            }
            if(mLevel->getEntityType(getGridPos(),i)==empty)
            {
               // now set the goal at the end of the ladder   
               goal->pos=getGridPos();
               goal->height=i;
            }
            else
            {
               goal->pos=getGridPos();
               goal->height=i-1;
            }
         }
         else
         { // we are not at a ladder
         
            // so find a ladder and set that position as our goal location
            bool found=false;
            for(int i=getGridPos();i>0 && !found;i--)
            {
               // if we find a ladder to our left
               if(mLevel->getEntityType(i,getGridHeight()) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
            if(!found) // then we didn't find a ladder so look right
            {
               for(int i=getGridPos();i<32;i++)
               {
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
            }
         }
      }else if(getRelativeDirection()==leftup)
      { // then the player is closer left and also above us
         // first check if we are at a ladder and if we are then go up
         // now check if we are already at a ladder
         std::cout << "leftup" << std::endl;
         if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
         {
            std::cout << "posType=ladder" << std::endl;
            // then set the goal at teh end of the ladder or at the height
            // of the player whichever is first
            // found is for the case that we find the node
            int i=0;
            for(i=getGridHeight();mLevel->getEntityType(getGridPos(), i)==ladder;i++)
            {
            }
            if(mLevel->getEntityType(getGridPos(),i)==empty)
            {
               // now set the goal at the end of the ladder   
               goal->pos=getGridPos();
               goal->height=i;
            }
            else
            {
               goal->pos=getGridPos();
               goal->height=i-1;
            }
         }
         else
         {
            // so find a ladder and set that position as our goal location
            bool found=false;
            for(int i=getGridPos();i>0 && !found;i--)
            {
               // if we find a ladder to our left
               if(mLevel->getEntityType(i,getGridHeight()) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
            if(!found) // then we didn't find a ladder so look left
            {
               for(int i=getGridPos()+1;i<32;i++)
               {
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
            }
         }
      }else if(getRelativeDirection()==downleft)
      { // the the player is closer below us and also to our left
         // so check if we are at a ladder
         // if the player is below us
         std::cout << "downleft" << std::endl;
         if(mPlayer->getGridHeight()<getGridHeight())
         {
            // then check if we are at a ladder to take us down
            if(mLevel->getEntityType(getGridPos(),getGridHeight()-1)==ladder)
            {
               // then set the goal at the end of the ladder or at the height
               // of the player whichever is first
               // found is for the case that we find the node
               int i;
               for(i=getGridHeight()-1;mLevel->getEntityType(getGridPos(),i)==ladder;i--)
               {
               }
               // now set the goal pos at the end of the ladder
               goal->pos=getGridPos();
               goal->height=i+1;
            }
            else // we are not at a ladder then piss around
            {
               // XXX: make this section look for a ladder that will take us
               // down.
               if(mLevel->getEntityType(getGridPos()-1, getGridHeight())!=brick)
               {
                  goal->pos=getGridPos()-1;
                  goal->height=getGridHeight();
               }else 
               {
                  goal->pos=getGridPos()+1;
                  goal->height=getGridHeight();
               }
               
            }
         } else
         {  // we weren't at a ladder so look for one first to our left then 
            //to our right
            bool found=false;
            for(int i=getGridPos();i>0 && !found;i--)
            {
               // if we find a ladder to our left
               if(mLevel->getEntityType(i,getGridHeight()) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
            if(!found) // then we didn't find a ladder so look left
            {
               for(int i=getGridPos()+1;i<32;i++)
               {
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
            }
         }
      }else if(getRelativeDirection()==leftdown)
      { // the player is closer left of us and also down from us
         // so find a ladder and set that position as our goal location
         std::cout << "leftdown" << std::endl;
         bool found=false;
         for(int i=getGridPos();i>0 && !found;i--)
         {
            // if we find a ladder to our right
            if(mLevel->getEntityType(i,getGridHeight()-1) == ladder)
            {
               found=true;
               goal->pos=i;
               goal->height=getGridHeight();
            }
            if(mLevel->getEntityType(i,getGridHeight()) == brick)
            {
               found=false;
               i=0;
            }
         }
         if(!found) // then we didn't find a ladder so look left
         {
            for(int i=getGridPos()+1;i<32;i++)
            {
               if(mLevel->getEntityType(i,getGridHeight()-1) == ladder)
               {
                  found=true;
                  goal->pos=i;
                  goal->height=getGridHeight();
               }
            }
         }
      }
   }
         
            
      
/*      // if we are closer horizontally then we are vertically
      if(abs(mPlayer->getGridHeight()-getGridHeight()) < abs(mPlayer->getGridPos()-getGridPos()))
      {
         // if the player is left of us
         if(mPlayer->getGridPos()<getGridPos())
         {
            // if the player is above us also
            if(mPlayer->getGridHeight()>getGridHeight())
            {
               // then look for a ladder to our left that goes up
               // found is so we can find out if there is no ladder
               bool found=false;
               for(int i=getGridPos()-1;i>0 && !found;i--)
               {
                  // if we find a ladder to our left
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
               if(!found)  // then we didn't find a ladder - so find one to our 
                           // right
               {
                  for(int i=getGridPos();i<32;i++)
                  {
                     if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                     {
                        found=true;
                        goal->pos=i;
                        goal->height=getGridHeight();
                     }
                  }
               }
            }// else the player is below us so we look for a ladder that will let us down
            else{
               // look for a ladder to our left that goes down
               // found is so we can find out if there is no ladder
               bool found=false;
               for(int i=getGridPos()-1;i>0 && !found;i--)
               {
                  // if we find a ladder to our left
                  if(mLevel->getEntityType(i,getGridHeight()-1)==ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
               if(!found) // if we didn't find a ladder to our left
               {
                  // search for one to our right
                  for(int i=getGridPos();i<32;i++)
                  {
                     if(mLevel->getEntityType(i,getGridHeight()-1) == ladder)
                     {
                        found=true;
                        goal->pos=i;
                        goal->height=getGridHeight();
                     }
                  }
               }
            }
         }
         else // else the player is right of us (but still closer horiz.)
         {
            // if the player is above us also
            if(mPlayer->getGridHeight()>getGridHeight())
            {
               // then look for a ladder to our right that goes up
               // found is so we can find out if there is no ladder
               bool found=false;
               for(int i=getGridPos()+1;i<32 && !found;i++)
               {
                  // if we find a ladder to our right
                  if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
               if(!found) // then we didn't find a ladder so look left
               {
                  for(int i=getGridPos();i>0;i--)
                  {
                     if(mLevel->getEntityType(i,getGridHeight()) == ladder)
                     {
                        found=true;
                        goal->pos=i;
                        goal->height=getGridHeight();
                     }
                  }
               }
            }// else the player is below us so we look for a ladder that will let us down
            else{
               // look for a ladder to our right that goes down
               // found is so we can find out if there is no ladder
               bool found=false;
               for(int i=getGridPos()+1;i<32 && !found;i++)
               {
                  // if we find a ladder to our right
                  if(mLevel->getEntityType(i,getGridHeight()-1)==ladder)
                  {
                     found=true;
                     goal->pos=i;
                     goal->height=getGridHeight();
                  }
               }
               if(!found)  // if we didn't find a ladder to our right so look 
                           // left
               {
                  // search for one to our left
                  for(int i=getGridPos();i>0;i--)
                  {
                     if(mLevel->getEntityType(i,getGridHeight()-1) == ladder)
                     {
                        found=true;
                        goal->pos=i;
                        goal->height=getGridHeight();
                     }
                  }
               }
            }
         }
      }else // we are closer vertically then horizontally 
      {
         // if the player is below us
         if(mPlayer->getGridHeight()<getGridHeight())
         {
            // then check if we are at a ladder to take us down
            if(mLevel->getEntityType(getGridPos(),getGridHeight()-1)==ladder)
            {
               // then set the goal at the end of the ladder or at the height
               // of the player whichever is first
               // found is for the case that we find the node
               bool found=false;
               int i;
               for(i=getGridHeight()-1;mLevel->getEntityType(getGridPos(),i)==ladder;i--)
               {
               }
               // now set the goal pos at the end of the ladder
               goal->pos=getGridPos();
               goal->height=i+1;
            }
            else // we are not at a ladder then piss around
            {
               if(mLevel->getEntityType(getGridPos()-1, getGridHeight())!=brick)
               {
                  goal->pos=getGridPos()-1;
                  goal->height=getGridHeight();
               }else 
               {
                  goal->pos=getGridPos()+1;
                  goal->height=getGridHeight();
               }
               
            }
         }
         else // the player is above us
         {
            // then check if we are at a ladder to take us up
            if(mLevel->getEntityType(getGridPos(), getGridHeight())==ladder)
            {
               // then set the goal at teh end of the ladder or at the height
               // of the player whichever is first
               // found is for the case that we find the node
               bool found=false;
               int i=0;
               for(i=getGridHeight();mLevel->getEntityType(getGridPos(), i)==ladder;i++)
               {
               }
               if(mLevel->getEntityType(getGridPos(),i)==empty)
               {
                  // now set the goal at the end of the ladder   
                  goal->pos=getGridPos();
                  goal->height=i;
               }
               else
               {
                  goal->pos=getGridPos();
                  goal->height=i-1;
               }
            }
            else
            {
               if(mLevel->getEntityType(getGridPos()-1, getGridHeight())!=brick)
               {
                  goal->pos=getGridPos()-1;
                  goal->height=getGridHeight();
               }else 
               {
                  goal->pos=getGridPos()+1;
                  goal->height=getGridHeight();
               }
            }
         }
      }
   }
*/
   void BadGuy::moveToGoal()
   {
      keyright=false;
      keyleft=false;
      keyup=false;
      keydown=false;
      if(goal->pos<getGridPos()) // then we need to move left
         keyleft=true;
      if(goal->pos>getGridPos())
         keyright=true;
      if(goal->height>getGridHeight())
      {
         keyup=true;
         keyleft=true;
      }
      if(goal->height<getGridHeight())
         keydown=true;
   }

   void BadGuy::update(float dt)
   {
      // if we are switching levels then return
      if(mLevel->nextLevel==true)
         return;
      
      // if we are in brick then we died and we need to be reset
      if(mLevel->getEntityType(getGridPos(), getGridHeight())==brick)
      {
         realHeight = initHeight;
         realPos = initPos;
         return;
      }

      if(mPlayer->amDead())
      {
         mLevel->readLevelFile(mPlayer);
         mLevel->resetBadGuys();
      }
         
      
      if(dt>(1.0/128.0))
         dt=(1.0/128.0);
      playerState tempState;
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
         tempState=climb;
         updateTex=true;
      }
      else if(keydown && ((onLadder() || ladderUnder()) && (!brickUnder() || brickUnder() && (int)realHeight%32!=0)))
      // we want to go down and we're on a ladder and there is no brick under
      // us, or if there is we're not at the bottom of this block
      {
         realHeight-=((128*dt));
         tempState=climb;
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
         tempState=runleft;
         updateTex=true;
      }
      else if(keyright && (solidUnder() || onLadder()) && !brickRight() && realPos<1008)
      // we want to go right and there is something under us there are no bricks
      // to our right and we aren't running off the screen
      { 
         realPos+=((128*dt));
         tempState=runright;
         updateTex=true;
      }
      else if(keyleft && onWire() && !brickLeft() && realPos>0)
      // we want to go left and there is a wire there and there are no bricks to
      // our left and we are not running off the screen
      {
         realPos-=((128*dt));
         tempState=hangleft;
         updateTex=true;
      }
      else if(keyright && onWire() && !brickRight() && realPos<1008)
      // we want to go right and there is a wire there and there are no bricks
      // to our right and we are not running off the screen
      {
         realPos+=((128*dt));
         tempState=hangright;
         updateTex=true;
      }

      if(isMoney())
      {
         mLevel->setEmpty(getGridPos(), getGridHeight());
         mLevel->numBagsDecr();
         if(mLevel->getNumBags()==0)
         {
            mLevel->nextLevel=true;
         }
      }

      if((initTime+=dt)>.08 && updateTex==true)
      {
         if(tempState==hangright)
         {
            if(mTextureState==hangright1){
               mTextureState=hangright2;
               currentTexture = hang2rightImage;
            }else if(mTextureState==hangright2){
               mTextureState=hangright3;
               currentTexture = hang3rightImage;
            }else{
               mTextureState=hangright1;
               currentTexture = hang1rightImage;
            }
         }else if(tempState==hangleft)
         {
            if(mTextureState==hangleft1){
               mTextureState=hangleft2;
               currentTexture = hang2leftImage;
            }else if(mTextureState==hangleft2){
               mTextureState=hangleft3;
               currentTexture = hang3leftImage;
            }else{
               mTextureState=hangleft1;
               currentTexture = hang1leftImage;
            }
         }else if(tempState==runright)
         {
            if(mTextureState==runright1){
               mTextureState=runright2;
               currentTexture = run2rightImage;
            }else if(mTextureState==runright2){
               mTextureState=runright3;
               currentTexture = run3rightImage;
            }else{
               mTextureState=runright1;
               currentTexture = run1rightImage;
            }
         }else if(tempState==runleft)
         {
            if(mTextureState==runleft1){
               mTextureState=runleft2;
               currentTexture = run2leftImage;
            }else if(mTextureState==runleft2){
               mTextureState=runleft3;
               currentTexture = run3leftImage;
            }else{
               mTextureState=runleft1;
               currentTexture = run1leftImage;
            }
         }else if(tempState==climb)
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
      if(mLevel->getEntityType(getGridPos()+1, getGridHeight()-1)==brick && (int)realPos%32>16)   
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

   void BadGuy::setInitPos(int p)
   {
      initPos = p;
   }

   void BadGuy::setInitHeight(int h)
   {
      initHeight = h;
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
      if(mLevel->getEntityType(getGridPos()-1, getGridHeight())==brick && (int)realPos%32<=1)
         return true;
      if((int)realHeight%32>8 && (mLevel->getEntityType(getGridPos(), getGridHeight()+1)==brick))
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
      if(mPlayer->getGridHeight()==getGridHeight() && mPlayer->getGridPos()==getGridPos())
      {
         mLevel->readLevelFile(mPlayer);
         mLevel->resetBadGuys();
         mPlayer->setLives(mPlayer->getLives()-1);
         mPlayer->caught();
         mPlayer->levelReset();
         std::cout << "caught" << std::endl;
      }

      
   }

   
      
   
} // end namespace


