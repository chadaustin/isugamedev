#ifndef MW_STORY_STATE_H
#define MW_STORY_STATE_H

#include <vector>
#include "State.h"
#include "Texture.h"


namespace mw
{
   class StoryState : public State
   {
   public:
      StoryState(Application*);
      ~StoryState();

      void update(float dt);
      void draw();
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);

   private:
      float mElapsedTime;
      int mCurrentFrame;
      int mCurrentCell;

      struct Cell
      {
         int frameNum;
         int x, y;
         int width, height;
         float waitTime;
         Texture* image;

         Cell()
            : image(0)
         {}

         Cell(int frame, int ax, int ay, int w, int h, float time, Texture* tex)
            : frameNum(frame), x(ax), y(ay), width(w), height(h), waitTime(time), image(tex)
         {}
      };

      std::vector<Cell> mCells;
   };
}


#endif
