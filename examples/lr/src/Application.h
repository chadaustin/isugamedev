#ifndef LR_APPLICATION_H
#define LR_APPLICATION_H

#include <list>
#include <SDL.h>

#include "GameState.h"
#include "IntroState.h"
#include "Types.h"


namespace lr
{
   class Application
   {
   public:
      /** constructor */
      Application();
      /** destructor */
      ~Application();

      void update(u64 elapsedTime);

      void draw();
      void resize(int w, int h);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      bool shouldQuit();

      int getWidth() const { return mWidth; }
      int getHeight() const { return mHeight; }

   private:

      int mWidth;
      int mHeight;
      
      // our states
      GameState* game;
      IntroState* intro;
      
      State* currentState;
   };
}

#endif
      
         
