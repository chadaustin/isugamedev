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
      void switchStates();
   private:
      Texture* mIntroImage;
      
   };
} // end namespace

#endif
