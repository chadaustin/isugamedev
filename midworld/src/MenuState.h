/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MenuState.h,v $
 * Date modified: $Date: 2003-03-11 01:24:33 $
 * Version:       $Revision: 1.12 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_MENU_STATE_H
#define MW_MENU_STATE_H

#include <vector>
#include <gltext.h>
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

      MenuPathTarget()
      {}

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

   class Application;
   class MenuState : public State
   {
   public:
      MenuState( Application* a );
      ~MenuState();

      void update(float dt);
      void draw();
      void onKeyPress(SDLKey sym, bool down);

   private:
      std::vector<Texture*> mImages;
      std::vector<MenuItem> mItemList; //list of all selectable menu items
      std::vector<MenuSquare> mSquares; //decorative, moving squares
      int mCurrentItem;

      gltext::FontPtr mFont;
      gltext::FontRendererPtr mFontRenderer;
   };
}


#endif
