#include <SDL_opengl.h>
#include "StoryState.h"
#include "StateFactory.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<StoryState> creator("Story");
   }

   StoryState::StoryState(Application* a) : State(a)
   {  
      mElapsedTime = 0;

      mFont = gltext::CreateFont("fonts/arial.ttf", gltext::PLAIN, 24);
      if (!mFont) {
         throw std::runtime_error("Cannot load font: fonts/arial.ttf");
      }

      mFontRenderer = gltext::CreateRenderer(gltext::PIXMAP);
      if (!mFontRenderer) {
         delete mFont;
         throw std::runtime_error("Cannot create gltext renderer");
      }
      mFontRenderer->setFont(mFont);
   }

   StoryState::~StoryState()
   {
      delete mFontRenderer;
      delete mFont;
   }

   void StoryState::update(float dt)
   {
      mElapsedTime += dt;
   }

   void StoryState::draw()
   {
      glClear(GL_COLOR_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, application().getWidth(), application().getHeight(), 0, 1, -1);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      //glTranslatef(0, 1 - mElapsedTime / 10000, 0);
      glColor3f(1, 1, 1);
      mFontRenderer->render("Hey bobby klein.  How goes it?");
   }

   void StoryState::onKeyPress(SDLKey sym, bool down)
   {
      invokeTransition("Game");
   }

   void StoryState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      invokeTransition("Game");
   }
}
