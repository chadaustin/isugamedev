/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Johnathan Gurley, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: Application.cpp,v $
 * Date modified: $Date: 2002-06-06 05:00:42 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <SDL/SDL_opengl.h>
#include "Application.h"

namespace mw
{
   Application::Application()
   {
      mWidth  = 0;
      mHeight = 0;
   }

   Application::~Application()
   {
   }

   void
   Application::update(u64 elapsedTime)
   {
   }

   void
   Application::draw()
   {
      // set up projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
//      float aspect_ratio = (mHeight == 0 ? 1 : float(mWidth) / mHeight);
      glOrtho(0, mWidth, mHeight, 0, -1, 1);
//      gluPerspective(45, aspect_ratio, 0.001f, 100);

      // set up view matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glBegin(GL_LINES);
      glColor3f(1, 1, 1);
      glVertex2f(0, 0);
      glVertex2f(mWidth, mHeight);
      glEnd();
   }

   void
   Application::resize(int width, int height)
   {
      mWidth  = width;
      mHeight = height;
   }

   void
   Application::onKeyPress(SDLKey sym, bool down)
   {
   }

   void
   Application::onMousePress(Uint8 button, bool down, int x, int y)
   {
   }

   void
   Application::onMouseMove(int x, int y)
   {
   }
}
