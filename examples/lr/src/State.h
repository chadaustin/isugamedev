#ifndef LR_STATE_H
#define LR_STATE_H

#include <assert.h>
#include <string>
#include <SDL.h>

namespace lr
{
   class Application;

   class State
   {
   public:
      State( Application* );
      virtual ~State();

      /** 
       * update is a pure virtual fuction that updates the state based on 
       * the amount of time passed.
       * @param dt is in seconds.
       */
      virtual void update(float dt) = 0;

      /**
       * draw method - pure virtual method that draws the scene
       */
      virtual void draw() = 0;

      /**
       * onKeyPress handles the keyboard input
       */
      virtual void onKeyPress(SDLKey sym, bool down) { }
      
      /**
       * handle the mouse down event from SDL
       * @params button is which button is pressed, down is true if the button
       * is now down and x and y are the screen coords of the pointer when the
       * button was pressed
       */
      virtual void onMousePress(Uint8 button, bool down, int x, int y){ }

      /**
       * handle the mouse move event 
       * @params x and y are the screen coords of the pointer 
       */
      virtual void onMouseMove(int x, int y){ }

      /**
       * return the application
       */
      Application& getApp(){ return *mApp; }
      
      /**
       * switchState is a pure virtual that is ment to be used by derived
       * classes to tell the application to change states to the next state
       */
      virtual int switchStates() = 0;

      void quit();
      bool isQuitting();

   private:
      bool mIsQuitting;
      Application* mApp;
   };
} // end namespace

#endif

      
      
         
