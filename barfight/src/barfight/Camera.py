from OpenGL.GL import glMultMatrixf
import gmtl

class Camera:
   def __init__(self):
      self.targetPos = gmtl.Point3f()
      self.lastTargetPos = gmtl.Point3f()
      self.targetRot = gmtl.Quatf()
      self.lastTargetRot = gmtl.Quatf()
      self.followDistance = 10
      self.followDistanceVel = 0
      self.maxFollowDistance = 15
      self.minFollowDistance = 5
      self.pitch = gmtl.deg2Rad(40.0)
      self.pitchVel = 0
      self.maxPitch = gmtl.deg2Rad(75.0)
      self.minPitch = gmtl.deg2Rad(15.0)
      self.transform = gmtl.Matrix44f()


   def setTarget(self, pos, rot):
      self.targetPos = pos
      self.targetRot = rot


   def update(self, dt):
      # Calculate our state updates assuming that our dt is twice as large so
      # that we get the impression that the camera moves half the distance
      camera_time = 2.0 * dt

      # Calculate the new rotation
      new_rot = gmtl.Quatf()
      gmtl.slerp(new_rot, camera_time, self.lastTargetRot, self.targetRot, True)
      self.lastTargetRot = new_rot

      # Calculate the new position
      new_pos = gmtl.Point3f()
      gmtl.lerp(new_pos, camera_time, self.lastTargetPos, self.targetPos)
      self.lastTargetPos = new_pos

      # Calculate the matrix for the target location
      new_rot_aa = gmtl.AxisAnglef()
      gmtl.set(new_rot_aa, new_rot)
      target_coord = gmtl.Coord3fAxisAngle(gmtl.Vec3f(new_pos), new_rot_aa)

      gmtl.set(self.transform, target_coord)

      # Apply the camera's offset information
      self.transform = self.transform * gmtl.makeRotMatrix44(
                              gmtl.AxisAnglef(-self.pitch, gmtl.Vec3f(1,0,0)))
      self.transform = self.transform * gmtl.makeTransMatrix44(
                              gmtl.Vec3f(0,0,self.followDistance))

      # Update pitch and follow distance by their velocities
      self.pitch           += self.pitchVel * dt
      self.followDistance  += self.followDistanceVel * dt

      # Check bounds on follow distance and pitch
      if self.followDistance > self.maxFollowDistance:
         self.followDistance = self.maxFollowDistance
      if self.followDistance < self.minFollowDistance:
         self.followDistance = self.minFollowDistance

      if self.pitch > self.maxPitch:
         self.pitch = self.maxPitch
      if self.pitch < self.minPitch:
         self.pitch = self.minPitch


   def draw(self):
      cam_inv = gmtl.makeInvert(self.transform)
      glMultMatrixf(getMatrixData(cam_inv))


   def setFollowDistance(self, distance):
      if distance > self.maxFollowDistance:
         self.followDistance = self.maxFollowDistance
      elif distance < self.minFollowDistance:
         self.followDistance = self.minFollowDistance
      else:
         self.followDistance = distance


   def setMaxFollowDistance(self, max):
      self.maxFollowDistance = max


   def setMinFollowDistance(self, min):
      self.minFollowDistance = min


   def setFollowDistanceVel(self, vel):
      self.followDistanceVel = vel


   def getPitch(self):
      return self.pitch


   def setPitch(self, angle):
      if angle > self.maxPitch:
         self.pitch = self.maxPitch
      else:
         self.pitch = angle


   def setMaxPitch(self, max):
      self.maxPitch = max


   def setMinPitch(self, min):
      self.minPitch = min


   def setPitchVel(self, vel):
      self.pitchVel = vel


   def getPos(self):
      return gmtl.makeTransVec(self.transform)



def getMatrixData(matrix):
   """
   Gets a tuple containing the data withing the given matrix.
   """
   return (matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
           matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
           matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
           matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3])

