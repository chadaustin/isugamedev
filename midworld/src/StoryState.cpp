#include <SDL_opengl.h>
#include <stdexcept>
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
      mStoryImage = new Texture("images/story.png");
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
      delete mStoryImage;
      delete mFontRenderer;
      delete mFont;
   }

   void StoryState::update(float dt)
   {
      mElapsedTime += dt;
   }

   void StoryState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);

      glClear(GL_COLOR_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, application().getWidth(), application().getHeight(), 0);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      //glTranslatef(0, 1 - mElapsedTime / 10000, 0);
      glColor3f(1, 1, 1);
      mStoryImage->drawRectangle(
         0, 0, application().getWidth(), application().getHeight());
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
