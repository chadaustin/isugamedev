
#include <phui/SDLBridge.h>
#include "BrothaApp.h"
#include "GameState.h"
#include <map>



namespace client {
   const float PI = 3.141579f;
   
   GameState::GameState() {
   }

   GameState::~GameState() {
   }

   void
   GameState::draw() {
      glClear(GL_COLOR_BUFFER_BIT);
   }

   void
   GameState::update(BrothaApp* app, int elapsedTime) {
   }

   void
   GameState::onKeyPress(SDLKey sym, bool down) {
   }

   void
   GameState::onMousePress(Uint8 button, bool down, int x, int y) {
   }

   void
   GameState::onMouseMove(int x, int y) {
   }
}
