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
       * NOTE: the vector b will be modified
       */
      void readLevelFile(Player* p, std::vector<BadGuy*>& b);

      /**
       * read a level file -- this is for if we need to call the read level file
       * from within a badguy where we cannot have access to a list of badguys
       * and therefore do not care about the list of badguys.
       */
      void readLevelFile(Player* p);

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

      /**
       * decrements the number of bags in the level
       */
      void numBagsDecr()
      {
         numBags--;
      }

      /**
       * sets the number of bags in the level
       */
      void setNumBags(int i)
      {
         numBags=i;
      }

      /**
       * gets the number of bags remaining in the level
       */
      int getNumBags()
      {
         return numBags;
      }

      /**
       * boolean for all guys in teh game to look at for if we are finished 
       * with this level.
       */
      bool nextLevel;

      /**
       * reset the levels so that currentLevel points to the first level in the
       * vector
       */
      void resetToFirstLevel()
      {
         setCurrentLevel(levelFiles.front());
      }

      void resetBadGuys();
      
   private:
      /**
       * this is a multi dimensional array for the representation of the level.
       * the level is acutally a 32hx24w grid and each slot can have nothing,
       * brick, ladder, or wire.  We call this grid our mLevel (aren't we clever)
       */
      positionType mLevel[32][24];

      /**
       * the only reason this should be used is for if a bad guy needs access to
       * all the other badguys like in the case of a reset of the level after 1
       * badguy catches the player.
       */
      std::vector<BadGuy*> mBadGuys;
      
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


      /**
       * a reference to the player
       */
      Player* mPlayer;
      
   };


} // end namespace

#endif
