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

   StoryState::StoryState(Application* a)
      : State(a)
      , mElapsedTime(0)
      , mCurrentFrame(0)
      , mCurrentCell(0)
   {
      mElapsedTime = 0;

      mCells.push_back(Cell(0,  87,  40,  373, 233,  0.0f, Texture::create("story1_frame1_cell1")));
      mCells.push_back(Cell(0, 460,   0,  376, 343,  5.0f, Texture::create("story1_frame1_cell2")));
      mCells.push_back(Cell(0,  87, 322,  442, 379, 10.0f, Texture::create("story1_frame1_cell3")));
      mCells.push_back(Cell(0, 529, 322,  369, 445, 15.0f, Texture::create("story1_frame1_cell4")));
      mCells.push_back(Cell(1,   0,   0, 1024, 768, 20.0f, Texture::create("story1_frame2_cell1")));
      mCells.push_back(Cell(25.0f));
   }

   StoryState::~StoryState()
   {}

   void StoryState::update(float dt)
   {
      mElapsedTime += dt;

      if (mElapsedTime >= mCells[mCurrentCell+1].waitTime)
      {
         ++mCurrentCell;
         if (mCells[mCurrentCell].frameNum > mCells[mCurrentFrame].frameNum)
         {
            mCurrentFrame = mCurrentCell;
         }
      }

      if ((unsigned)mCurrentCell == mCells.size()-1)
      {
         invokeTransition("Load");
      }
   }

   void StoryState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);

      glClearColor(1,1,1,1);
      glClear(GL_COLOR_BUFFER_BIT);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, application().getWidth(), application().getHeight(), 0);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glColor3f(1, 1, 1);

      for (int i=mCurrentFrame; i<=mCurrentCell; ++i)
      {
         if (mCells[i].image != 0)
         {
            mCells[i].image->drawRectangle(mCells[i].x,
                                           mCells[i].y,
                                           mCells[i].x + mCells[i].width,
                                           mCells[i].y + mCells[i].height);
         }
      }
   }

   void StoryState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         invokeTransition("Load");
      }
   }

   void StoryState::onMousePress(Uint8 button, bool down, int x, int y)
   {
      if (down)
      {
         invokeTransition("Load");
      }
   }
}
