#ifndef LR_LEVEL_H
#define LR_LEVEL_H

#include <SDL_opengl.h>
#include <list>
#include <vector>

#include "Block.h"
#include "Texture.h"
#include "Types.h"


namespace lr
{
   // forward declarations
   class Player;
   class BadGuy;
   
  

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
       * this method reads the current level file in
       */
      void readLevelFile(Player* p, BadGuy* b);

      /**
       * this method loads all the level files in the given vector into the
       * level class so we can iterate over them.
       */
      void loadLevelFiles(std::vector<std::string> theLevels);

      /**
       * returns the vector of level names
       */
      std::vector<std::string> getLevels();

      /**
       * returns the currentLevel pointer
       */
      std::string getCurrentLevel();

      /**
       * sets teh currentLevel pointer to the given string
       */
      void setCurrentLevel(std::string l);

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
       * in the removedBlocks list.  The dt helps us flip through the animation
       * at constant speed.
       * Returns true when the bricks are gone otherwise returns false
       */
      bool burn(const int& x, const int& y, float dt);

      
      /**
       * the update method is used to update the level when bricks are being 
       * removed or added.
       */
      void update(float dt);

      /** 
       * draw simply draws the level to the screen
       */
      void draw();

      void numBagsDecr()
      {
         numBags--;
      }

      void setNumBags(int i)
      {
         numBags=i;
      }

      int getNumBags()
      {
         return numBags;
      }
         
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
      Texture* brickBurn1Image;
      Texture* brickBurn2Image;
      Texture* brickBurn3Image;
      Texture* brickBurn4Image;
      Texture* ladderImage;
      Texture* wireImage;
      Texture* moneyImage;

      /**
       * the number of money bags in the level
       */
      int numBags;

      /**
       * the amount of time gone by since we started burning out a hole in the
       * ground.
       */
      float burnTime;
      Block* burnBlock;
      int burnTextureNum;
      
      /**
       * we maintain a list of blocks that have been removed
       */
      std::list<Block*> removedBlocks;

      /**
       * this is a vector of all the names of the files that we load in
       */
      std::vector<std::string> levelFiles;

      /**
       * this is a pointer to the current levelFile
       */
      std::string currentLevelFile;
      
   };


} // end namespace

#endif
