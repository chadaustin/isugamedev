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
# File:          $RCSfile: Player.py,v $
# Date modified: $Date: 2003-06-03 03:56:17 $
# Version:       $Revision: 1.3 $
# -----------------------------------------------------------------
############################################################## barfight-cpr end
from OpenGL.GL import *

import siren
import gmtl

from Util import *

class Player:
   def __init__(self, name, avatarType):
      self.name = name
      self.avatar = siren.Avatar.create(avatarType)
      self.avatar.setWCS(gmtl.EulerAngleXYZf(gmtl.deg2Rad(-90.0), 0, 0))
      self.avatar.triggerAnimationCycle('IDLE')
      self.drunkAmount = 0.0

      self.pos = gmtl.Point3f(0,0,0)
      self.rot = gmtl.Quatf()

      self.vel = gmtl.Vec3f(0,0,0)

      # Change in yaw is used to control rotation from mouse-look
      self.yawChange = 0.0


   def update(self, dt):
      self.avatar.update(dt)

      # Update the player's rotation
      if self.yawChange != 0.0:
         # Update the player's rotation to match the new rotation
         yaw_rot = gmtl.makeRotQuat(
                     gmtl.makeRotMatrix44(
                        gmtl.AxisAnglef(-self.yawChange, gmtl.Vec3f(0,1,0))))
         self.rot = self.rot * yaw_rot

         # Reset the yaw change since we took care of it
         self.yawChange = 0.0

      # Move the player
      self.pos = self.pos + self.vel * dt


   def draw(self):
      glPushMatrix()
      glTranslatef(self.pos[0], self.pos[1], self.pos[2])

      # Make the rotation matrix
      rot = gmtl.Matrix44f()
      gmtl.setRot(rot, self.rot)

      glMultMatrixf(getMatrixData(rot))

      self.avatar.render()
      
      glPopMatrix()


   def getName(self):
      return self.name


   def getAvatar(self):
      return self.avatar
