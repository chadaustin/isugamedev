from OpenGL.GL import *
from OpenGL.GLU import *
from siren import *

PI = 3.141579

def deg2Rad(ang):
   return ang * PI / 180.0

class PyAvatarState(State):
   def __init__(self):
      State.__init__(self)
      self.ignoreMouseMove = 1
      self.rotX = 0
      self.rotY = 0
      self.avatar = Avatar('John')
      self.avatar.triggerAnimationCycle('DANCE')

      # For FPS calculations
      self.fps = 0.0
      self.frameTimes = 0.0
      self.numFrames = 0

   def update(self, dt):
#      print 'dt: '+str(dt)
      self.avatar.update(dt)

      self.frameTimes += dt
      self.numFrames += 1
      if self.frameTimes > 1.0:
#         print 'time: ' + str(self.frameTimes)
#         print 'frames: ' + str(self.numFrames)
         self.fps = self.numFrames / self.frameTimes
         self.frameTimes = 0.0
         self.numFrames = 0
         print 'FPS: ' + str(self.fps)

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

      glTranslate(0, 0.0, -10.0)

      glEnable(GL_DEPTH_TEST)
      self.avatar.render()

   def onMousePress(self, button, down, x, y):
      if down:
         self.quit()

   def onMouseMove(self, x, y):
      if self.ignoreMouseMove:
         self.ignoreMouseMove = 0
         return

      centerX = self.width / 2
      centerY = self.height / 2
      diffX = x - centerX
      diffY = y - centerY

      self.rotX += diffX
      self.rotY += diffY

      WarpMouse(centerX, centerY)
      self.ignoreMouseMove = 1

   def onKeyPress(self, key, down):
      print 'key down: ' + str(down)
      if key == Key.ESCAPE:
         self.quit()


class PyAvatarStateCreator(StateCreator):
   def create(self):
      return PyAvatarState()

creator = PyAvatarStateCreator()
StateFactory().register('PyAvatar', creator)

kernel = Kernel()
kernel.start('PyAvatar')
