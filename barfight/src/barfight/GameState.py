############################################################## barfight-cpr beg
#
# barfight - an all-out brawl in the local pub
# barfight is (C) Copyright 2003 by members of the
#    Iowa State University Game Developers Club
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
# -----------------------------------------------------------------
# File:          $RCSfile: GameState.py,v $
# Date modified: $Date: 2003-06-03 03:56:17 $
# Version:       $Revision: 1.3 $
# -----------------------------------------------------------------
############################################################## barfight-cpr end
from OpenGL.GL import *
from OpenGL.GLU import *
import siren
import gmtl

from Camera import *
from Player import *

class GameState(siren.State):
   def __init__(self):
      siren.State.__init__(self)
      self.ignoreMouseMove = True
      self.fps = 0.0
      self.numFrames = 0
      self.frameTime = 0.0

      # Initialize the input controls
      self.initInput()

      self.camera = Camera()

      # Create the player
      self.player = Player('Ben', 'John')
      self.player.pos = gmtl.Point3f(0, 0, -5)

      rot = gmtl.Quatf()
#      gmtl.set(rot, gmtl.AxisAnglef(gmtl.deg2Rad(180), 0,1,0))
      self.player.rot = rot

      # Big hack to get player rotation control to work
      self.vel_change = gmtl.Vec3f()

      self.npcs = []
      for i in range(4):
         av = siren.Avatar.create('John')
         av.setWCS(gmtl.EulerAngleXYZf(gmtl.deg2Rad(-90.0), 0, 0))
         av.setPos(gmtl.Vec3f(4.0*i, 0, -10))
         av.triggerAnimationCycle('DANCE')
         self.npcs.append(av)

      self.curAnim = 0
      self.anims = ['WALK',
                    'RUN',
                    'DANCE',
                    'IDLE',
                    'TYPE',
                    'SIT',
                    'WORK1',
                    'WORK2']

      # Create the texture to hold the motion blur
      self.blurTexture = siren.Texture(512, 512, 3, GL_RGB)

      # Inite the GL state
      glEnable(GL_DEPTH_TEST)
      glEnable(GL_TEXTURE_2D)
      glClearColor(0,0,0,1)


   def initInput(self):
      '''
      Initializes the input system, setting up all the appropriate bindings.
      '''
      # Load in the input bindings
      self.inputMgr = siren.InputManager()
      self.inputMgr.loadMappings('data/inputbindings.txt')

      # Movement
      self.actionForward         = self.inputMgr.getAction('FORWARD')
      self.actionBackward        = self.inputMgr.getAction('BACKWARD')
      self.actionStrafeLeft      = self.inputMgr.getAction('STRAFE_LEFT')
      self.actionStrafeRight     = self.inputMgr.getAction('STRAFE_RIGHT')

      # Camera control (for debugging)
      self.actionCameraZoomIn    = self.inputMgr.getAction('CAMERA_ZOOM_IN')
      self.actionCameraZoomOut   = self.inputMgr.getAction('CAMERA_ZOOM_OUT')
      self.actionCameraPitchUp   = self.inputMgr.getAction('CAMERA_PITCH_UP')
      self.actionCameraPitchDown = self.inputMgr.getAction('CAMERA_PITCH_DOWN')

      # Application control
      self.actionQuit            = self.inputMgr.getAction('QUIT')


   def draw(self):
      '''
      Renders a visualization of the current state of the game simulation.
      '''
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

      glMatrixMode(GL_PROJECTION)
      glLoadIdentity()
      gluPerspective(80.0, float(self.getWidth()) / self.getHeight(),
                     0.01, 500.0)

      glMatrixMode(GL_MODELVIEW)
      glLoadIdentity()
      self.camera.draw()

      # Redraw the current blur texture
      glPushAttrib(GL_VIEWPORT_BIT)

      # Change the viewport to match the size of the texture
      glViewport(0, 0, self.blurTexture.getTexWidth(),
                       self.blurTexture.getTexHeight())
      self.drawMotionBlur(self.player.drunkAmount)
      self.drawScene()

      # Copy the contents of the frame buffer into our blur texture
      self.blurTexture.bind()
      glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0,
                       self.blurTexture.getTexWidth(),
                       self.blurTexture.getTexHeight(),
                       0)
      self.blurTexture.unbind()

      # Clear the fram buffer again
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
      glPopAttrib()

      # Blend in the motion blur with the background color
      self.drawMotionBlur(self.player.drunkAmount)

      # Draw the scene on top of the motion blur
      self.drawScene()


   def update(self, dt):
      '''
      Updates the game simulation based on the amount of time that has passed
      since the previous frame.
      '''
      # Update the input system
      self.updateInput(dt)

      # Update the avatar
      self.player.update(dt)

      # Update the camera
      self.camera.setTarget(self.player.pos, self.player.rot)
      self.camera.update(dt)

      for i in range(len(self.npcs)):
         self.npcs[i].update(dt)

      # Calculate the FPS
      self.numFrames += 1
      self.frameTime += dt
      if self.frameTime > 0.5:
         self.fps = float(self.numFrames) / self.frameTime
         self.frameTime = 0.0
         self.numFrames = 0
         print 'FPS: %f' % (self.fps)


   def updateInput(self, dt):
      '''
      Updates the state of the input system and processes all currently active
      actions.
      '''
      # Update the input manager
      self.inputMgr.update(dt)

      # Movement
      speed = 5
      accel    = gmtl.Vec3f(0, 0, speed)
      reverse  = gmtl.Vec3f(0, 0, -speed * 0.7)
      sleft    = gmtl.Vec3f( speed * 0.9, 0, 0)
      sright   = gmtl.Vec3f(-speed * 0.9, 0, 0)

#      vel_change = gmtl.Vec3f(0,0,0)
      self.vel_change = self.vel_change + accel   * self.actionForward.getEdgeState()
      self.vel_change = self.vel_change + reverse * self.actionBackward.getEdgeState()
      self.vel_change = self.vel_change + sleft   * self.actionStrafeLeft.getEdgeState()
      self.vel_change = self.vel_change + sright  * self.actionStrafeRight.getEdgeState()

      # Update the current velocity
      forward = gmtl.Vec3f()
      gmtl.xform(forward, self.player.rot, gmtl.Vec3f(self.vel_change))
      self.player.vel = forward
#      self.player.vel = self.player.vel + forward


   def onKeyPress(self, sym, down):
      '''
      Called when the state of a key has changed.
      '''
      self.inputMgr.onKeyPress(sym, down)

      if down:
         if sym == siren.Key.SDLK_ESCAPE or sym == siren.Key.SDLK_q:
            self.quit()

         elif sym == siren.Key.SDLK_SPACE:
            self.player.getAvatar().stopAnimation(self.anims[self.curAnim])
            self.curAnim = (self.curAnim + 1) % len(self.anims)
            self.player.getAvatar().triggerAnimationCycle(self.anims[self.curAnim])

         elif sym == siren.Key.SDLK_LCTRL:
            self.player.drunkAmount += 0.05
            if self.player.drunkAmount > 1.0:
               self.player.drunkAmount = 1.0

         elif sym == siren.Key.SDLK_LALT:
            self.player.drunkAmount -= 0.05
            if self.player.drunkAmount < 0.0:
               self.player.drunkAmount = 0.0


   def onMousePress(self, button, down, x, y):
      '''
      Called when the state of a mouse button has changed.
      '''
      self.inputMgr.onMousePress(button, down)


   def onMouseMove(self, x, y):
      '''
      Called when the mouse has been moved to a new position.
      '''
      # If we just warped the mouse to the center, ignore that movement
      if self.ignoreMouseMove:
         self.ignoreMouseMove = False
         return

      # Compute the offset of the mouse from the center
      center = gmtl.Point2i(self.getWidth() / 2, self.getHeight() / 2)
      diff = gmtl.Point2f(x - center[0], y - center[1])

      # Compute change in yaw for player rotation cnotrol
      yaw = float(x - center[0]) / 180.0
      self.player.yawChange += yaw

      # Put the mouse back in the center of the screen
      siren.WarpMouse(center[0], center[1])
      self.ignoreMouseMove = True


   def drawMotionBlur(self, decay):
      '''
      Renders the motion blur texture to the screen.
      '''
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

      # Turn off depth testing so that we blend over the screen
      glDisable(GL_DEPTH_TEST)

      # Enable blending
      glBlendFunc(GL_SRC_ALPHA, GL_ONE)
      glEnable(GL_BLEND)

      # Decrease alpha value of the blend by 10% so that it will fade
      glColor4f(1, 1, 1, decay)

      # Switch to an orthograhic view
      glMatrixMode(GL_PROJECTION)
      glPushMatrix()

      glLoadIdentity()
      gluOrtho2D(0, self.getWidth(), self.getHeight(), 0)

      glMatrixMode(GL_MODELVIEW)
      glPushMatrix()
      glLoadIdentity()

      # Blend the texture into the screen
      self.blurTexture.bind()
      glBegin(GL_QUADS)

      glTexCoord2f(0, 1); glVertex2f(0, 0)
      glTexCoord2f(0, 0); glVertex2f(0, self.getHeight())
      glTexCoord2f(1, 0); glVertex2f(self.getWidth(), self.getHeight())
      glTexCoord2f(1, 1); glVertex2f(self.getWidth(), 0)

      glEnd()
      self.blurTexture.unbind()

      glPopMatrix()
      glMatrixMode(GL_PROJECTION)

      # Switch back to the old projection
      glPopMatrix()
      glMatrixMode(GL_MODELVIEW)

      glPopAttrib()


   def drawScene(self):
      # Draw the grid
      drawGrid()

      # Draw the axes
      drawAxes()

      # Draw the avatar
      self.player.draw()

      for i in range(len(self.npcs)):
         self.npcs[i].render()


def drawGrid():
   glPushAttrib(GL_LIGHTING_BIT)
   glDisable(GL_LIGHTING)

   extent = 1000

   glColor3f(0,0,1)
   glBegin(GL_LINES)
   for i in range(-extent, extent):
      glVertex3f(-extent, 0, i)
      glVertex3f( extent, 0, i)

      glVertex3f(i, 0,  extent)
      glVertex3f(i, 0, -extent)
   glEnd()

   glPopAttrib()


def drawAxes():
   glPushAttrib(GL_LIGHTING_BIT)
   glDisable(GL_LIGHTING)

   glLineWidth(2)
   glBegin(GL_LINES)
   # X axis
   glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(3,0,0)
   # Y axis
   glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,3,0)
   # Y axis
   glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,3)
   glEnd()
   glLineWidth(1)

   glPopAttrib()
