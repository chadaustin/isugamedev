
#include <phui/SDLBridge.h>
#include "BrothaApp.h"
#include "GarageState.h"
#include <map>



namespace client {
   const float PI = 3.141579f;
   
   GarageState::GarageState() {
   }

   GarageState::~GarageState() {
   }

   void
   GarageState::draw() {
      glClear(GL_COLOR_BUFFER_BIT);
   }

   void
   GarageState::update(BrothaApp* app, int elapsedTime) {
   }

   void
   GarageState::onKeyPress(SDLKey sym, bool down) {
   }

   void
   GarageState::onMousePress(Uint8 button, bool down, int x, int y) {
   }

   void
   GarageState::onMouseMove(int x, int y) {
   }
}
