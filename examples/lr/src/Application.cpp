#include <SDL_opengl.h>

#include "Application.h"
#include "GameState.h"
#include "IntroState.h"

namespace lr
{
   Application::Application() 
      : mWidth(0)
      , mHeight(0)
   {
      intro = new IntroState(this);
      game = new GameState(this);
      currentState = intro;
   }

   Application::~Application()
   {
   }


   void Application::update(u64 elapsedTime)
   {
      // convert time to seconds
      float dt = static_cast<float>(elapsedTime) / 1000000.0f;

      currentState->update(dt);
      

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
      return currentState->isQuitting();
   }

} // end namespace
