#ifndef LR_INTRO_STATE_H
#define LR_INTRO_STATE_H

#include "State.h"

namespace lr
{
   class Application;
   class Texture;

   class IntroState : public State
   {
   public:
      IntroState( Application* a);
      ~IntroState();

      /**
       * implementation of update from State class
       */
      void update(float dt);

      /**
       * implementation of draw from State class
       */
      void draw();

      /**
       * implementation of onKeyPress from State class
       */
      void onKeyPress(SDLKey sym, bool down);

      /** 
       * implmentation of switchState from State class
       */
      bool switchStates();
   private:
      Texture* mIntroImage;
      Texture* select;
      Texture* guy1;
      Texture* guy2;
      // pointer to the current texture
      Texture* currentTexture;
      // up and down keys for looking through the menu choices
      bool keyup, keydown, transition;

      float initTime;
      int offset;
      
   };
} // end namespace

#endif
