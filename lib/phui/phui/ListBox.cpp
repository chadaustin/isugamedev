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
 * Date modified: $Date: 2002-05-03 08:42:35 $
 * Version:       $Revision: 1.12 $
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
#include "FontRendererCache.h"
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

      FontRenderer* renderer = FontRendererCache::getFontRenderer(getFont());

      const Insets& i = getInsets();
//      int w = width  - i.getLeft() - i.getRight();
//      int h = height - i.getTop()  - i.getBottom();
      unsigned int fontHeight = renderer->getHeight();
//      unsigned int fontWidth = renderer.getWidth(mText);
      unsigned int fontAscent = fontHeight - renderer->getDescent();

      int textRectX = i.getLeft();
      int textRectY = i.getTop();
//      int textRectW = width  - (i.getRight()  + textRectX);
//      int textRectH = height - (i.getBottom() + textRectY);

      int fontX = textRectX;
      int fontY = textRectY + fontAscent;

      for (int x = 0; x < int(mItems.size()); ++x) {
         if (mSelectedItem == x) {
            // draw the selected box
            glColor(getForegroundColor());
            glBegin(GL_TRIANGLE_FAN);
               glVertex2i(0,     fontHeight*x);
               glVertex2i(width, fontHeight*x);
               glVertex2i(width, fontHeight*(x+1));
               glVertex2i(0,     fontHeight*(x+1));
            glEnd();
            glColor(getBackgroundColor());
         }
         renderer->draw(mItems[x], fontX, fontY+(x*fontHeight));
         if(mSelectedItem == x) {
            glColor(getForegroundColor());
         }
      }
   }

   void ListBox::add(const std::string& text) {
      mItems.push_back(text);
   }

   void ListBox::remove(unsigned int idx) {
      if (idx <= mItems.size()) {
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

   void ListBox::onMouseDown(InputButton button, const Point& p) {
      if (button == BUTTON_LEFT) {
         FontRenderer* renderer = FontRendererCache::getFontRenderer(getFont());
         unsigned int selectedIdx = (p.y-(p.y%renderer->getHeight()))/renderer->getHeight();
         // Check that the computed index isn't outside our list of values
         if (selectedIdx <= mItems.size()) {
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
