import appconnect
from phui import *

print 'You rock!'

# Get the root widget of the UI
ui = appconnect.getUI()

# Create a new button
b = createButton()
b.text = 'Python Button'
b.position.set(20, 10)
b.size.set(150, 25)

# Add a button to the UI
ui.add(b)

print 'Success!'
