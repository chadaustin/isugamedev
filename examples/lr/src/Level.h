#ifndef LR_LEVEL_H
#define LR_LEVEL_H

#include <SDL_opengl.h>
#include <list>

#include "Texture.h"
#include "Types.h"

namespace lr
{
   // forward declarations
   class Player;
   class BadGuy;
   
   /**
    * helper class to deal with when the player burns a block out 
    */
   class Block
   {
   public:
      Block(int p, int h)
      {
         time = 0;
         pos = p;
         height = h;
      }
      ~Block(){}
      int pos;
      int height;
      float time; // the time past since the block was last done anything with
   };

   class Level{
   public:

      /**
       * constructor
       */
      Level();

      /**
       * destructor
       */
      ~Level();

      /**
       * this method reads a level file in
       */
      void readLevelFile(const std::string& file, Player* p, BadGuy* b);

      /**
       * this method returns the entity type at a given location in the level
       */
      positionType getEntityType(const int& width, const int& height);
         
      /**
       * this method sets the given location in the levelgrid to empty
       */
      void setEmpty(const int& x, const int& y);

      /** 
       * this method sets the given location in the levelgrid to be a brick
       */
      void setBrick(const int& x, const int& y);

      /** 
       * mark a position to be burned - that is removed temporarily by being placed 
       * in the removedBlocks list
       */
      void burn(const int& x, const int& y);

      
      /**
       * the update method is used to update the level when bricks are being 
       * removed or added.
       */
      void update(float dt);

      /** 
       * draw simply draws the level to the screen
       */
      void draw();


   private:
      /**
       * this is a multi dimensional array for the representation of the level.
       * the level is acutally a 32hx24w grid and each slot can have nothing,
       * brick, ladder, or wire.  We call this grid our mLevel (aren't we clever)
       */
      positionType mLevel[32][24];

      /**
       * various textures that we need
       */
      Texture* brickImage;
      Texture* ladderImage;
      Texture* wireImage;
      Texture* moneyImage;

      /**
       * the number of money bags in the level
       */
      int numBags;

      /**
       * we maintain a list of blocks that have been removed
       */
      std::list<Block*> removedBlocks;

   };


} // end namespace

#endif
