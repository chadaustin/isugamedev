#ifndef LR_HELP_STATE_H
#define LR_HELP_STATE_H

#include "State.h"

namespace lr
{
   class Application;
   class Texture;

   class HelpState : public State
   {
   public:
      HelpState( Application* a);
      ~HelpState();

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
      int switchStates();
   private:
      Texture* mHelpImage;
      
      
      // up and down keys for looking through the menu choices
      bool transition;

   };
} // end namespace

#endif
