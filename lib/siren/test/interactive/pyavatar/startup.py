from siren import *

class PyAvatarState(State):
   def update(self, dt):
      print 'dt: '+str(dt)

   def draw(self):
      print 'draw'

class PyAvatarStateCreator(StateCreator):
   def create(self):
      return PyAvatarState()

creator = PyAvatarStateCreator()

#factory = getStateFactory()
StateFactory().register('PyAvatar', creator)

kernel = Kernel()
kernel.start('PyAvatar')
