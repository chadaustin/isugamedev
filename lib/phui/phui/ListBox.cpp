/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ListBox.cpp,v $
 * Date modified: $Date: 2002-12-31 06:24:07 $
 * Version:       $Revision: 1.15 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Josh Carlson, Ben Scott
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
 ************************************************************** phui-cpr-end */
#include "ListBox.h"
#include <GL/gl.h>
#include "WidgetContainer.h"
#include <algorithm>
#include <assert.h>

namespace phui {

   ListBox::ListBox()
      : mSelectedItem(-1)
   {
   }

   ListBox::~ListBox() {
   }

   void ListBox::draw() {
      const Size& size = getSize();
      const int width = size.getWidth();
      const int height = size.getHeight();
      gltext::FontPtr font = getFont();

      // draw the box background
      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
         glVertex2i(0,     0     );
         glVertex2i(width, 0     );
         glVertex2i(width, height);
         glVertex2i(0,     height);
      glEnd();

      // draw text
      glColor(getForegroundColor());

      gltext::FontRendererPtr renderer = gltext::CreateRenderer(gltext::PIXMAP);
      renderer->setFont(font.get());

      int fontHeight = font->getAscent() + font->getDescent();
      int fontLineGap = font->getLineGap();
      int itemHeight = fontHeight+fontLineGap;

      glPushMatrix();
      glTranslatef(3.0,0.0,0.0);
      for(int x = 0; x < int(mItems.size()); ++x)
      {
         glTranslatef(0.0, float(fontLineGap + fontHeight), 0.0);
         if(mSelectedItem == x)
         {
            // draw the selected box
            glColor(getForegroundColor());
            glPushMatrix();
            glTranslatef(-3.0, float(-(fontHeight+2)), 0.0);
            glBegin(GL_TRIANGLE_FAN);
               glVertex2i(0,     0);//fontHeight*x);
               glVertex2i(width, 0);//fontHeight);//*x);
               glVertex2i(width, fontHeight+3);//*(x+1));
               glVertex2i(0,     fontHeight+3);//*(x+1));
            glEnd();
            glColor(getBackgroundColor());
            glPopMatrix();
         }

         renderer->render(mItems[x].c_str());
         if(mSelectedItem == x) 
         {
            glColor(getForegroundColor());
         }
      }
      glPopMatrix();
   }

   void ListBox::add(const std::string& text) {
      mItems.push_back(text);
   }

   void ListBox::remove(unsigned int idx) {
      if (idx < mItems.size()) {
         mItems.erase(mItems.begin() + idx);

         if(idx == mSelectedItem) {
            mSelectedItem = -1;
         }
      }
   }

   void ListBox::clear() {
      mSelectedItem = -1;
      mItems.clear();
   }

   const std::string& ListBox::get(unsigned int idx) const {
      assert(idx < mItems.size() && "Out of bounds!");
      return mItems[idx];
   }

   int ListBox::getSelectedIndex() const {
      return mSelectedItem;
   }

   void ListBox::onMouseDown(InputButton button, const Point& p) 
   {
      if (button == BUTTON_LEFT) 
      {
         const Size& size = getSize();
         const int height = size.getHeight();
         gltext::FontPtr font = getFont();

         unsigned int itemHeight = font->getAscent() + font->getDescent() + font->getLineGap();
        
         unsigned int selectedIdx = unsigned int((p.y-(p.y%itemHeight))/double(itemHeight));
         // Check that the computed index isn't outside our list of values
         if (selectedIdx < mItems.size()) 
         {
            mSelectedItem = selectedIdx;
            std::cout<<"Selected index "<<mSelectedItem<<"/"<<mItems.size()<<std::endl;
            fireListSelectionEvent(mSelectedItem);
         }
      }
   }

   void ListBox::addListSelectionListener(ListSelectionListener* listener) {
      mListeners.push_back(listener);
   }

   void ListBox::removeListSelectionListener(ListSelectionListener* listener) {
      ListenerIter itr;
      itr = std::find(mListeners.begin(), mListeners.end(), listener);
      if (itr != mListeners.end()) {
         mListeners.erase(itr);
      }
   }

   void ListBox::fireListSelectionEvent(int selectedIdx) {
      ListSelectionEvent evt(this, selectedIdx);

      for(ListenerIter itr=mListeners.begin(); itr!=mListeners.end(); itr++) {
         (*itr)->onListSelection(evt);
      }
   }
} // namespace phui
