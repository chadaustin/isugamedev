import siren
import gmtl

class Player:
   def __init__(self, name, avatarType):
      self.name = name
      self.avatar = siren.Avatar.create(avatarType)
      self.avatar.setWCS(gmtl.EulerAngleXYZf(gmtl.deg2Rad(-90.0), 0, 0))


   def update(self, dt):
      self.avatar.update(dt)


   def getName(self):
      return self.name


   def getAvatar(self):
      return self.avatar
