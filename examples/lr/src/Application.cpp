#include <SDL_opengl.h>

#include "Application.h"
#include "GameState.h"
#include "IntroState.h"
#include "HelpState.h"

namespace lr
{
   Application::Application() 
      : mWidth(0)
      , mHeight(0)
   {
      intro = new IntroState(this);
      game = new GameState(this);
      help = new HelpState(this);
      currentState = intro;

      isQuitting = false;
   }

   Application::~Application()
   {
   }


   void Application::update(u64 elapsedTime)
   {
      // convert time to seconds
      float dt = static_cast<float>(elapsedTime) / 1000000.0f;

      currentState->update(dt);
      
      if(currentState->switchStates()==1)
      {
         if(currentState==intro)
            currentState = game;
         else if(currentState==help)
            currentState = intro;
         else if(currentState==game)
            currentState = intro;
      }else if(currentState->switchStates()==3)
      {
         currentState = help;
      }else if(currentState->switchStates()==4)
      {
         isQuitting=true;
      }
      
      
   }
      
   void Application::draw()
   {
      currentState->draw();
   }

   void Application::resize(int width, int height)
   {
      mWidth = width;
      mHeight = height;
   }

   void Application::onKeyPress(SDLKey sym, bool down)
   {
      currentState->onKeyPress(sym, down);
   }

   void Application::onMousePress(Uint8 button, bool down, int x, int y)
   {
      currentState->onMousePress(button, down, x,y);
   }

   void Application::onMouseMove(int x, int y)
   {
      currentState->onMouseMove(x,y);
   }

   bool Application::shouldQuit()
   {
      return isQuitting;
   }

} // end namespace
