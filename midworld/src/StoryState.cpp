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

      mCells.push_back(Cell(0,  87,  40,  373, 233,  0.0f, new Texture("images/story1_frame1_cell1.jpg")));
      mCells.push_back(Cell(0, 460,   0,  376, 343,  4.0f, new Texture("images/story1_frame1_cell2.jpg")));
      mCells.push_back(Cell(0,  87, 322,  442, 379,  8.0f, new Texture("images/story1_frame1_cell3.jpg")));
      mCells.push_back(Cell(0, 529, 322,  369, 445, 12.0f, new Texture("images/story1_frame1_cell4.jpg")));
      mCells.push_back(Cell(1,   0,   0, 1024, 768, 16.0f, new Texture("images/story1_frame2_cell1.jpg")));
      mCells.push_back(Cell(20.0f));
   }

   StoryState::~StoryState()
   {
      // Delete all textures allocated
      for (std::vector<Cell>::iterator itr = mCells.begin(); itr != mCells.end(); ++itr)
      {
         delete (*itr).image;
      }
   }

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
