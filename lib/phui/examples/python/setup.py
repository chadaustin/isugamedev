/* -*- Mode:  -*- */
// vim:
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
 * File:          $RCSfile: setup.py,v $
 * Date modified: $Date: 2005-01-25 23:11:39 $
 * Version:       $Revision: 1.12 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
import appconnect
from phui import *

print 'You rock!'

class MyActionListener(ActionListener):
   def onAction(self, evt):
      global wnd
      wnd.visible = not wnd.visible

class MyWindowListener(WindowListener):
   def onWindowOpened(self, evt):
      print 'window opened'
   def onWindowClosed(self, evt):
      print 'window closed'
   def onWindowFocused(self, evt):
      print 'window focused'
   def onWindowUnfocused(self, evt):
      print 'window unfocused'

# Get the root widget of the UI
ui = appconnect.getUI()

# Create a new window
wnd = createWindow()
wnd.position.set(10, 10)
wnd.size.set(300, 45)
wnd.backgroundColor.set(0,1,0,1)
wnd.backgroundColor.set(0,1,0,1)
wnd.addWindowListener(MyWindowListener())
wnd.show()

# Create a new button
b = createButton()
b.text = 'Python Button'
b.position.set(20, 10)
b.size.set(150, 25)
b.backgroundColor.set(0,0,1,1)
b.foregroundColor.set(0,0,0,1)

c = createCheckBox()
c.checked = True
c.position.set(180, 10)
c.size.set(20, 20)
c.backgroundColor = b.backgroundColor
c.foregroundColor.set(1,1,1,1)

# Add the widgets to the UI
wnd.add(b)
wnd.add(c)
ui.add(wnd)

# Create a button for the window made in C++
b2 = createButton()
b2.text = 'Another Py Button'
b2.position.set(5, 100)
b2.size.set(110, 25)
b2.backgroundColor.set(0,0,1,1)
b2.foregroundColor.set(0,0,0,1)

lbl = createLabel()
lbl.text = 'Choose A Beer'
lbl.position.set(130, 10)
lbl.size.set(100, 20)
lbl.backgroundColor.set(0,0,1,0.5)

beer_list = createListBox()
beer_list.add('Corona')
beer_list.add('XX')
beer_list.add('Michelob')
beer_list.add('Guinness')
beer_list.position.set(130, 30)
beer_list.size.set(100, 70)

beer_btn = createButton()
beer_btn.text = 'Drink'
beer_btn.position.set(170, 105)
beer_btn.size.set(60, 25)
beer_btn.backgroundColor.set(0,0,1,0.5)
beer_btn.addActionListener(MyActionListener())

txt = createTextField()
txt.text = "I'm a text box"
txt.position.set(5, 150)
txt.size.set(80, 20)
txt.backgroundColor.set(1,1,1,1)
txt.foregroundColor.set(0,0,0,0)

wnd2 = ui.getWidget(0)
wnd2.add(b2)
wnd2.add(lbl)
wnd2.add(beer_list)
wnd2.add(beer_btn)
wnd2.add(txt)

print 'Success!'
