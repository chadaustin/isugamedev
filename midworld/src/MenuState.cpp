/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "MenuState.h"
#include "GameState.h"




namespace mw
{


   MenuState::MenuState()
   {
      mImages.resize(2);
    
      mImages[0] = new Texture("menu_bg.jpeg");
      mImages[1] = new Texture("menu_selection.png");      
      
      mItemList.resize(5);
      
      for(int i=0;i<5;i++)
      {
      	 mItemList[i].x=70;
         mItemList[i].y=260+28*i;
      	 mItemList[i].height=25;
      }

      mItemList[MENU_NEW].width=115;
      mItemList[MENU_LOAD].width=120;
      mItemList[MENU_OPTIONS].width=90;
      mItemList[MENU_CREDITS].width=83;
      mItemList[MENU_QUIT].width=55;
      
      mCurrentItem = 0;
   }

   MenuState::~MenuState()
   {
      for (int i = 0; i < int(mImages.size()); ++i)
      {
         delete mImages[i];
      }
      mImages.clear();
   }

      
   void
   MenuState::update(u64 elapsedTime)
   {
   }

   void
   MenuState::draw()
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
      glOrtho(0, 640, 480, 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glColor4f(1, 1, 1, 1);
      mImages[0]->drawRectangle(0,0,640,480);	//draw background
      
      glColor4f(.8f,.9f,1,0.5f);
      mImages[1]->drawRectangle( mItemList[mCurrentItem].x,
	             	      	 mItemList[mCurrentItem].y,
	             	      	 mItemList[mCurrentItem].x + mItemList[mCurrentItem].width,
	             	      	 mItemList[mCurrentItem].y + mItemList[mCurrentItem].height);
   
   }

   void
   MenuState::onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         switch (sym)
         {
            case SDLK_DOWN:
               mCurrentItem = (mCurrentItem + 1) % 5;
               break;
            case SDLK_UP:
               mCurrentItem = (mCurrentItem + 4) % 5;
               break;
            case SDLK_RETURN:
               switch (mCurrentItem)
               {
                  case 0:
                     invokeTransition(new GameState());
                     break;
                  case 4:
                     quit();
                     break;
               }
               break;
         }
      }
   }

   void
   MenuState::onMousePress(Uint8 button, bool down, int x, int y)
   {
   }

   void
   MenuState::onMouseMove(int x, int y)
   {
      mMouseX = x;
      mMouseY = y;
   }

}
