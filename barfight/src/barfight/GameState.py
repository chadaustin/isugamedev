from OpenGL.GL import *
from OpenGL.GLU import *
import siren
import gmtl

from Camera import *
from Player import *

class GameState(siren.State):
   def __init__(self):
      siren.State.__init__(self)
      self.drunkAmount = 0.0
      self.ignoreMouseMove = True
      self.fps = 0.0
      self.numFrames = 0
      self.frameTime = 0.0

      self.camera = Camera()

      self.player = Player('Ben', 'John')

      rot = gmtl.Quatf()
      gmtl.set(rot, gmtl.AxisAnglef(gmtl.deg2Rad(180), 0,1,0))
      self.player.getAvatar().setRot(rot)

      self.npcs = []
      for i in range(4):
         av = siren.Avatar.create('John')
         av.setWCS(gmtl.EulerAngleXYZf(gmtl.deg2Rad(-90.0), 0,0))
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


   def draw(self):
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
      self.drawMotionBlur()
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
      self.drawMotionBlur()

      # Draw the scene on top of the motion blur
      self.drawScene()


   def update(self, dt):
      # Update the avatar
      self.player.update(dt)

      # Update the camera
      self.camera.setTarget(self.player.getAvatar().getPos(),
                            self.player.getAvatar().getRotQuat())
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


   def onKeyPress(self, sym, down):
      if down:
         if sym == siren.Key.SDLK_ESCAPE or sym == siren.Key.SDLK_q:
            self.quit()

         elif sym == siren.Key.SDLK_SPACE:
            self.player.getAvatar().stopAnimation(self.anims[self.curAnim])
            self.curAnim = (self.curAnim + 1) % len(self.anims)
            self.player.getAvatar().triggerAnimationCycle(self.anims[self.curAnim])

         elif sym == siren.Key.SDLK_LCTRL:
            self.drunkAmount += 0.05
            if self.drunkAmount > 1.0:
               self.drunkAmount = 1.0

         elif sym == siren.Key.SDLK_LALT:
            self.drunkAmount -= 0.05
            if self.drunkAmount < 0.0:
               self.drunkAmount = 0.0

   def onMouseMove(self, x, y):
      if self.ignoreMouseMove:
         self.ignoreMouseMove = False
         return

      center = gmtl.Point2i(self.getWidth() / 2, self.getHeight() / 2)
      diff = gmtl.Point2f(x - center[0], y - center[1])

      siren.WarpMouse(center[0], center[1])
      self.ignoreMouseMove = True


   def drawMotionBlur(self):
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      # Turn off depth testing so that we blend over the screen
      glDisable(GL_DEPTH_TEST);

      # Enable blending
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      glEnable(GL_BLEND);

      # Decrease alpha value of the blend by 10% so that it will fade
#         float decay = mDrunkAmount;
      decay = 0.95;
      glColor4f(1, 1, 1, decay);

      # Switch to an orthograhic view
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();

      glLoadIdentity();
      gluOrtho2D(0, self.getWidth(), self.getHeight(), 0);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      # Blend the texture into the screen
      self.blurTexture.bind();
      glBegin(GL_QUADS);

      glTexCoord2f(0, 1); glVertex2f(0, 0);
      glTexCoord2f(0, 0); glVertex2f(0, self.getHeight());
      glTexCoord2f(1, 0); glVertex2f(self.getWidth(), self.getHeight());
      glTexCoord2f(1, 1); glVertex2f(self.getWidth(), 0);

      glEnd();
      self.blurTexture.unbind();

      glPopMatrix();
      glMatrixMode(GL_PROJECTION);

      # Switch back to the old projection
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);

      glPopAttrib();


   def drawScene(self):
      glPushMatrix()

      # Draw the avatar
      glTranslate(0, -5.0, -5.0)
      self.player.getAvatar().render()

      for i in range(len(self.npcs)):
         self.npcs[i].render()

      glPopMatrix()
