from OpenGL.GL import *
from OpenGL.GLU import *
from siren import *

PI = 3.141579

def deg2Rad(ang):
   return ang * PI / 180.0

class PyAvatarState(State):
   def __init__(self):
      State.__init__(self)
      self.rotX = 0
      self.rotY = 0

   def update(self, dt):
      print 'dt: '+str(dt)

   def draw(self):
      glClearColor(0,0,1,0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

      glMatrixMode(GL_PROJECTION)
      glLoadIdentity()
      gluPerspective(80.0, float(self.width)/self.height, 0.01, 500.0)

      glMatrixMode(GL_MODELVIEW)
      glLoadIdentity()
      glRotatef(deg2Rad(self.rotX)*5.0, 1,0,0)
      glRotatef(deg2Rad(self.rotY)*5.0, 0,1,0)

      glTranslate(0, -5.0, -10.0)

   def onMousePress(self, button, down, x, y):
      if down:
         self.quit()

class PyAvatarStateCreator(StateCreator):
   def create(self):
      return PyAvatarState()

creator = PyAvatarStateCreator()
StateFactory().register('PyAvatar', creator)

kernel = Kernel()
kernel.start('PyAvatar')
