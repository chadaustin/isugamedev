import appconnect
from phui import *

print 'You rock!'

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
lbl.text = 'BPL v2 is hella-cool!'
lbl.position.set(130, 10)
lbl.size.set(130, 25)
lbl.backgroundColor.set(0,0,1,0.5)

list = createListBox()
list.add('Corona')
list.add('XX')
list.add('Michelob')
list.add('Guinness')
list.position.set(130, 40)
list.size.set(70, 70)

wnd2 = ui.getWidget(0)
wnd2.add(b2)
wnd2.add(lbl)
wnd2.add(list)

print 'Success!'
