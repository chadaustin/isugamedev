#include "Application.h"
#include "CreditsState.h"

namespace mw
{
   CreditsState::CreditsState( Application* a ) : State( a )
   {
      mImages.push_back( new Texture("credits.jpeg") );
   }

   void CreditsState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glClear(GL_COLOR_BUFFER_BIT);

      /// @todo  we assume 640x480...  :(

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, this->application().getWidth(), this->application().getHeight(), 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glColor4f(1, 1, 1, 1);
      mImages[0]->drawRectangle(0,0,this->application().getWidth(), this->application().getHeight());	// draw background
   }
}
