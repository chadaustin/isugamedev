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

print 'Success!'
