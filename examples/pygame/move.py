import sys                   # basic python stuff like sys.exit()
import pygame                # bring in the pygame module
from pygame.locals import *  # put common pygame symbols in the global namespace


class Point:

    # this is the constructor for the class
    # self is like 'this' in Java or C++
    # the rest of the arguments are passed in when you call the class name
    # like a function
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y
        
    # for convenience, allow conversion of a point object a tuple
    def as_tuple(self):
        return (self.x, self.y)


# initialize pygame
pygame.init()

# set a 640x480 double-buffered display
screen = pygame.display.set_mode((640, 480), DOUBLEBUF)

# load our images...
# the .convert() bit converts the image to an optimal format for blitting,
# speeding things up.  .convert_alpha() lets us use the alpha channel for
# transparency
background = pygame.image.load('background.png').convert()
head       = pygame.image.load('head.png').convert_alpha()

# create a clock object to throttle our framerate
clock = pygame.time.Clock()

# head position on the screen
position = Point()
position.x = (640 - head.get_width()) / 2
position.y = (480 - head.get_height()) / 2

def display():
    screen.blit(background, (0, 0))
    screen.blit(head, position.as_tuple())
    pygame.display.flip()

def handle_input():
    # grab the tuple of keypress states
    keys = pygame.key.get_pressed()
    if keys[K_LEFT]:
        position.x -= 1
    if keys[K_RIGHT]:
        position.x += 1
    if keys[K_UP]:
        position.y -= 1
    if keys[K_DOWN]:
        position.y += 1

# infinite game loop
done = 0
while not done:

    clock.tick(60)  # 60 frames per second

    # handle events!
    for event in pygame.event.get():

        # has the user clicked the close button?
        if event.type is QUIT or event.type is KEYDOWN and event.key is K_ESCAPE:
            sys.exit()
        # do we want to go to fullscreen mode?
        elif event.type is KEYDOWN and event.key == K_f:
            print "toggling fullscreen"
            # this only works on some platforms
            pygame.display.toggle_fullscreen()

        # for arrow key presses, we just poll every frame

    # update caption with FPS
    pygame.display.set_caption('Moving Head - FPS %d' % clock.get_fps())

    handle_input()
    display()
