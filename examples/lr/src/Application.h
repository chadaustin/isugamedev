#ifndef LR_APPLICATION_H
#define LR_APPLICATION_H

#include <list>
#include <SDL.h>


#include "Types.h"
#include "State.h"


namespace lr
{
   // forward declarations
   class GameState;
   class HelpState;
   class IntroState;

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

      bool isQuitting;
      
      // our states
      GameState* game;
      IntroState* intro;
      HelpState* help;
      
      State* currentState;
   };
}

#endif
      
         
