import appconnect
from phui import *

print 'You rock!'

class MyActionListener(ActionListener):
   def onAction(evt):
      global wnd
      wnd.visible = not wnd.visible

# Get the root widget of the UI
ui = appconnect.getUI()

# Create a new window
wnd = createWindow()
wnd.position.set(10, 10)
wnd.size.set(300, 45)
wnd.backgroundColor.set(0,1,0,1)
wnd.backgroundColor.set(0,1,0,1)
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
