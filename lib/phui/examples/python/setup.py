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

# Add th widgets to the UI
wnd.add(b)
ui.add(wnd)

# Create a button for the window made in C++
b2 = createButton()
b2.text = 'Another Python Button'
b2.position.set(50, 100)
b2.size.set(200, 25)
b2.backgroundColor.set(0,0,1,1)
b2.foregroundColor.set(0,0,0,1)

wnd2 = ui.getWidget(0)
wnd2.add(b2)

print 'Success!'
