#include <iostream>
#include <SDL_opengl.h>

#include "Level.h"

namespace lr
{

   void Level::draw(){
   }


   Level::Level()
   {
   }


   Level::~Level()
   {
   }

   void Level::readLevelFile(const std::string& file)
   {
      /*
      for(int i=0;i<24;i++) // for all the rows
      {
         for(int j=0;j<32;j++) // for all the columns
         {
        */    
   }

   positionType getEntityType(const int& width, const int& height)
   {
      positionType p;
      p = empty;
      return p;
   }

} // end namespace

