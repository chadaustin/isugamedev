#include <fstream>
#include <iostream>
#include <SDL_opengl.h>
#include <vector>

#include "Level.h"
#include "Player.h"
#include "BadGuy.h"

namespace lr
{

   bool Level::burn(const int& x, const int& y, float dt)
   { 
      if (burnTime==0)
         // XXX: this is a mem leak needs to be fixed
         burnBlock = new Block(x,y);
      burnTime+=dt;
      if(burnTime<.25)
      {
         if(burnTime<.25)
            burnTextureNum=4;
         if(burnTime<.2)
            burnTextureNum=3;
         if(burnTime<.15)
            burnTextureNum=2;
         if(burnTime<.1)
            burnTextureNum=1;
         if(burnTime<.05)
            burnTextureNum=0;
         
      }
      else
      {
         // XXX: this is a memory leak that I will need to fix later
         removedBlocks.push_front(burnBlock);
         burnTime=0;
         return true;
      }
      return false;
   }

   void Level::update(float dt)
   {      
      // first add in dt then check to see if time is > 3 if it is remove it from the list
      for (std::list<Block*>::iterator itr = removedBlocks.begin(); itr != removedBlocks.end(); ++itr)
      {
         (*itr)->time+=dt;
         if((*itr)->time>3.0)
         {
            setBrick((*itr)->pos, (*itr)->height);
            removedBlocks.erase(itr);
            itr = removedBlocks.end();
         }else
         {
            setEmpty((*itr)->pos, (*itr)->height);
         }
      }
   }
 
   void Level::draw(){
      
      for(int i=0;i<24;i++) // for all the rows
      {
         for(int j=0;j<32;j++)  // for all the cols
         {
            if(mLevel[j][i] == brick)
            {
               brickImage->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
               if(burnTime>0)
               {
                  if(burnBlock->pos==j && burnBlock->height==i)
                  {
                     if(burnTextureNum==0)
                        brickImage->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
                     else if(burnTextureNum==1)
                        brickBurn1Image->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
                     else if(burnTextureNum==2)
                        brickBurn2Image->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
                     else if(burnTextureNum==3)
                        brickBurn3Image->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
                     else if(burnTextureNum==4)
                        brickBurn4Image->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
                  }
               }
            }else if(mLevel[j][i] == wire)
            {
               wireImage->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
            }else if(mLevel[j][i] == ladder)
            {
               ladderImage->drawRectangle(j*32,i*32,(j+1)*32,(i+1)*32);
            }
            else if(mLevel[j][i] == money)
            {
               moneyImage->drawRectangle(j*32,(i+1)*32,(j+1)*32,i*32);
            }
         }
      }
   }
            
   void Level::setEmpty(const int& x, const int& y)
   {
      mLevel[x][y] = empty;
   }
      
   void Level::setBrick(const int& x, const int& y)
   {
      mLevel[x][y] = brick;
   }

   Level::Level()
   {
      brickImage = Texture::create(std::string("Brick.png"));
      brickBurn1Image = Texture::create(std::string("Brick-burn1.png"));
      brickBurn2Image = Texture::create(std::string("Brick-burn2.png"));
      brickBurn3Image = Texture::create(std::string("Brick-burn3.png"));
      brickBurn4Image = Texture::create(std::string("Brick-burn4.png"));
            
      ladderImage = Texture::create(std::string("ladder.png"));
      wireImage = Texture::create(std::string("wire.png"));
      moneyImage = Texture::create(std::string("money.png"));

      // initialize the number of bags to 0
      numBags = 0;
      burnTime = 0.0;
      burnTextureNum=0;
   }


   Level::~Level()
   {
      delete brickImage;
      delete brickBurn1Image;
      delete brickBurn2Image;
      delete brickBurn3Image;
      delete brickBurn4Image;
      delete ladderImage;
      delete wireImage;
      delete moneyImage;
   }

   void Level::readLevelFile(const std::string& file, Player* p, BadGuy* b)
   {
      std::ifstream in;
      in.open(file.c_str());
      int temp;
      for(int i=0;i<24;i++) // for all the rows
      {
         for(int j=0;j<32;j++) // for all the columns
         {
            in >> temp;
            if(temp==0)
            {
               mLevel[j][i] = empty;
            }else if(temp==1)
            {
               mLevel[j][i] = brick;
            }else if(temp==2)
            {
               mLevel[j][i] = ladder;
            }else if(temp==3)
            {
               mLevel[j][i] = wire;
            }else if(temp==4)
            {
               mLevel[j][i] = money;
               numBags++;
            }else if(temp==5){
               mLevel[j][i] = empty;
               b->setHeight(i*32);
               b->setPos(j*32);
            }
            else if(temp==6){
               mLevel[j][i] = empty;
               p->setHeight(i*32);
               p->setPos(j*32);
            }
         }
      }
      in.close();
   }

   positionType Level::getEntityType(const int& width, const int& height)
   {
      positionType p;
      p = mLevel[width][height];
      return p;
   }

} // end namespace

