#ifndef LR_LEVEL_H
#define LR_LEVEL_H

#include <SDL_opengl.h>

#include "Texture.h"
#include "Types.h"

namespace lr
{

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
      void readLevelFile(const std::string& file);

      /**
       * this method returns the entity type at a given location in the level
       */
      positionType getEntityType(const int& width, const int& height);
         

      void draw();

   private:
      /**
       * this is a multi dimensional array for the representation of the level.
       * the level is acutally a 32hx24w grid and each slot can have nothing,
       * brick, ladder, or wire.  We call this grid our mLevel (aren't we clever)
       */
      positionType mLevel[32][24];

   };


} // end namespace

#endif
