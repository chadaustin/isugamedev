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
 * File:          $RCSfile: MenuState.cpp,v $
 * Date modified: $Date: 2002-10-01 01:00:28 $
 * Version:       $Revision: 1.16 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <math.h>
#include "StateFactory.h"
#include "MenuState.h"
#include "Application.h"

namespace mw
{
   namespace
   {
      StateCreatorImpl<MenuState> creator("Menu");
   }

   MenuState::MenuState( Application* a ) : State( a )
   {
      mCursor.init( this->application().getWidth(), 
                    this->application().getHeight() );
      
      //setup images
      mImages.resize(3);

      mImages[0] = new Texture("images/menu_bg.jpeg");
      mImages[1] = new Texture("images/menu_selection.png");
      mImages[2] = new Texture("images/menu_square.png");

      //setup menu items
      mItemList.resize(5);

      for(int i=0; i<5; i++)
      {
         mItemList[i].x = 70;
         mItemList[i].y = 260 + 28*i;
         mItemList[i].height = 25;
      }

      mItemList[MENU_NEW].width = 115;
      mItemList[MENU_LOAD].width = 120;
      mItemList[MENU_OPTIONS].width = 90;
      mItemList[MENU_CREDITS].width = 83;
      mItemList[MENU_QUIT].width = 55;

      mCurrentItem = 0;

      //setup decorative squares and paths
      mSquares.resize(4);

      for(int i=0; i<4; i++)
      {
         mSquares[i].path.resize(4);
      }

      //this is the path we want all the squares to take
      mSquares[0].path[0] = MenuPathTarget(600, 140, 0.1f);
      mSquares[0].path[1] = MenuPathTarget(600, 240, 0.1f);
      mSquares[0].path[2] = MenuPathTarget(300, 240, 0.1f);
      mSquares[0].path[3] = MenuPathTarget(300, 140, 0.1f);

      for(unsigned int i=0; i<4; i++)
      {
         mSquares[i].path = mSquares[0].path;
         mSquares[i].targetIndex = 1; //head towards first path target
         mSquares[i].x = 100 + 15*i;
         mSquares[i].y = 240;
         mSquares[i].width = mSquares[i].height = 10;
         mSquares[i].alpha = 0.3f;
      }
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
   MenuState::update(float dt)
   {
      mCursor.update( this->application().getWidth(), 
                      this->application().getHeight() );
      //TODO: make this work!  Andres
/*
      float dt=(float)elapsedTime/1000000.f;
	 //move squares
      for(unsigned int i=0;i<mSquares.size();i++)
      {

	 //all temporary variables, because the struct path is long
	
	 float x,y,tx,ty,dx,dy;  //distance to target
	 float newX,newY;  //next position of square
	 float speed;
      	
	
	 x=mSquares[i].x;
	 y=mSquares[i].y;
	
	 tx=mSquares[i].path[mSquares[i].targetIndex].x;
	 ty=mSquares[i].path[mSquares[i].targetIndex].y;
	
	 speed = mSquares[i].path[mSquares[i].targetIndex].approachSpeed;
	
	
	 //distance components to target
      	 dx=tx-x;
      	 dy=ty-y;

	 //distance to target
	 float d=sqrt(dx*dx + dy*dy);
	 dx/=d;
	 dy/=d;

      	 //next square position
	 newX=(float)x + (dx * dt * speed);
 	 newY=(float)y + (dy * dt * speed);

	 //if the square has hit the target or jumped over it
	 if((int)tx==(int)newX && (int)ty==(int)newY)
	 {
	    newX=tx;
	    newY=ty;
	    mSquares[i].targetIndex++;

	    //loop the paths
	    if(mSquares[i].targetIndex >= mSquares[i].path.size())
	       mSquares[i].targetIndex=0;
	 }
	 //update square positions
	 mSquares[i].x=(int)newX;
	 mSquares[i].y=(int)newY;
      }*/
   }

   void
   MenuState::draw()
   {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glClear(GL_COLOR_BUFFER_BIT);

      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, this->application().getWidth(), this->application().getHeight(), 0, -1, 1);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      // draw background
      glColor4f(1, 1, 1, 1);
      mImages[0]->drawRectangle(0,0,this->application().getWidth(), this->application().getHeight());

      // draw selection blur
      glColor4f(.8f,.9f,1,0.5f);
      mImages[1]->drawRectangle(
            mItemList[mCurrentItem].x,
            mItemList[mCurrentItem].y,
            mItemList[mCurrentItem].x + mItemList[mCurrentItem].width,
            mItemList[mCurrentItem].y + mItemList[mCurrentItem].height);
/*    //draw each square
      for(int i=0;i<int(mSquares.size());i++)
      {
	 glColor4f(1,1,1,mSquares[i].alpha);
      	 mImages[2]->drawRectangle( mSquares[i].x,
	             	      	    mSquares[i].y,
      	             	      	    mSquares[i].x + mSquares[i].width,
      	             	      	    mSquares[i].y + mSquares[i].height);
	
      }
  */
        
        mCursor.draw( this->application().getWidth(), 
                      this->application().getHeight() );
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
            case 27:
               quit();
               break;
            case SDLK_RETURN:
               switch (mCurrentItem)
               {
                  case 0:
                     invokeTransition("Game");
                     break;
                  case 3:
                     invokeTransition("Credits");
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
   MenuState::onMouseMove(int x, int y)
   {
      mCursor.onMouseMove( this->application().getWidth(), 
                           this->application().getHeight(), x, y );
   }
}
