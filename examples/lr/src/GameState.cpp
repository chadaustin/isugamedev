#include <iostream>
#include <string>

#include <SDL_opengl.h>

#include "GameState.h"

namespace lr
{
   GameState::GameState(Application* app) : State(app)
   {
      
   }

   GameState::~GameState()
   {
   }

   void GameState::draw()
   {
   }

   void GameState::update(float dt)
   {
   }

   void GameState::switchStates()
   {
   }

   void GameState::onKeyPress(SDLKey sym, bool down)
   {
   }


} // end namespace
