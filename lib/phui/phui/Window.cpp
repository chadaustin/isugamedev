/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * File:          $RCSfile: Window.cpp,v $
 * Date modified: $Date: 2005-01-23 21:46:48 $
 * Version:       $Revision: 1.20 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifdef _MSC_VER
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif
#include <GL/gl.h>
#include "Window.h"

namespace phui
{
   Window::Window()
      : mTitle("")
   {
      init("", false);
   }

   Window::Window(const std::string& title)
      : mTitle(title)
   {
      init(title, false);
   }

   Window::~Window()
   {}

   WindowPtr Window::create()
   {
      WindowPtr obj(new Window());
      return obj;
   }

   WindowPtr Window::create(const std::string& title)
   {
      WindowPtr obj(new Window(title));
      return obj;
   }

   void Window::draw()
   {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();

      // render the background
      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
      {
         glVertex2i(0,     0);
         glVertex2i(width, 0);
         glVertex2i(width, height);
         glVertex2i(0,     height);
      }
      glEnd();

      if (hasFocus())
      {
         glColor(getForegroundColor());
         glBegin(GL_LINE_LOOP);
         {
            glVertex2i(0,     0);
            glVertex2i(width, 0);
            glVertex2i(width, height);
            glVertex2i(0,     height);
         }
         glEnd();
      }

      WidgetContainer::draw();
   }

   void Window::setVisible(bool visible)
   {
      bool wasVisible = isVisible();

      Widget::setVisible(visible);

      // Let our listeners know about us.
      if (visible)
      {
         // Fire a window opened event if the window is not already visible
         if (! wasVisible)
         {
            fireWindowOpenedEvent();
         }
      }
      else
      {
         // Fire a window closed event if this call closed the window
         if (wasVisible)
         {
            fireWindowClosedEvent();
         }
      }
   }

   void Window::addWindowListener(WindowListenerPtr listener)
   {
      mListeners.push_back(listener);
   }

   void Window::removeWindowListener(WindowListenerPtr listener)
   {
      ListenerIter itr;
      itr = std::find(mListeners.begin(), mListeners.end(), listener);
      if (itr != mListeners.end())
      {
         mListeners.erase(itr);
      }
   }

   void Window::init(const std::string& title, bool visible)
   {
      mTitle = title;
      Widget::setVisible(visible);
   }

   void Window::fireWindowOpenedEvent()
   {
      //XXX:  Fix this...
      //WindowEvent evt(boost::shared_dynamic_cast<Window>(getSelf()));
      WindowEvent evt(this);
      for (ListenerIter itr=mListeners.begin(); itr!=mListeners.end(); ++itr)
      {
         (*itr)->onWindowOpened(evt);
      }
   }

   void Window::fireWindowClosedEvent()
   {
      //XXX:  Fix this...
      //WindowEvent evt(boost::shared_dynamic_cast<Window>(getSelf()));
      WindowEvent evt(this);
      for (ListenerIter itr=mListeners.begin(); itr!=mListeners.end(); ++itr)
      {
         (*itr)->onWindowClosed(evt);
      }
   }
}
