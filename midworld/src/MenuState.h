/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_MENU_STATE_H
#define MW_MENU_STATE_H


#include <vector>
#include "State.h"
#include "Texture.h"




namespace mw
{
   //array references of menu items in mItemList
   
   enum
   {
      MENU_NEW=0,
      MENU_LOAD,
      MENU_OPTIONS,
      MENU_CREDITS,
      MENU_QUIT
   };
   
   //path target for moving menu squares
   //contains target coordinates and speed
   //at which to approach it
   struct MenuPathTarget
   {
      int x,y;
      float approachSpeed;
      MenuPathTarget(){}
      MenuPathTarget(int X,int Y, float speed)
      {
	 x=X;
	 y=Y;
	 approachSpeed=speed;
      }

      MenuPathTarget(const MenuPathTarget &src)
      {
	 x=src.x; y=src.y; approachSpeed=src.approachSpeed;
      }
      
      void operator=(const MenuPathTarget &src)
      {
	 x=src.x; y=src.y; approachSpeed=src.approachSpeed;
      }
   };
      
   //decorative moving squares in the menu
   //contains coordinates and a path target vector
   struct MenuSquare
   {
      int x,y;
      int width,height;
      std::vector<MenuPathTarget> path;      
      unsigned int targetIndex;
      float alpha;
   };
   
   //this keeps track of all the selectable menu items on the screen
   //the data is used to draw a selection picture over the current 
   //menu-item
   
   struct MenuItem
   {
      int x;
      int y;
      unsigned int width;
      unsigned int height;
   };	
   
   class MenuState : public State
   {
   public:
      MenuState();
      ~MenuState();

      void update(u64 elapsedTime);
      void draw();
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

   private:
      std::vector<Texture*> mImages;
      std::vector<MenuItem> mItemList; //list of all selectable menu items      
      std::vector<MenuSquare> mSquares; //decorative, moving squares
      int mCurrentItem;
      int mMouseX;
      int mMouseY;
   };
}


#endif
