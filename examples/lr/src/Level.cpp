#include <fstream>
#include <iostream>
#include <SDL_opengl.h>

#include "Level.h"

namespace lr
{

   void Level::draw(){
      for(int i=0;i<24;i++) // for all the rows
      {
         for(int j=0;j<32;j++)  // for all the cols
         {
            if(mLevel[j][i] == brick)
            {
               brickImage->drawRectangle(j*32,i*32,(j+1)*32,(i+1)*32);
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
      


   Level::Level()
   {
      brickImage = Texture::create(std::string("Brick.png"));
      ladderImage = Texture::create(std::string("ladder.png"));
      wireImage = Texture::create(std::string("wire.png"));
      moneyImage = Texture::create(std::string("money.png"));

      // initialize the number of bags to 0
      numBags = 0;
   }


   Level::~Level()
   {
      delete brickImage;
      delete ladderImage;
      delete wireImage;
      delete moneyImage;
   }

   void Level::readLevelFile(const std::string& file)
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

