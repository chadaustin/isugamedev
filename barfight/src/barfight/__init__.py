import string
__build__   = 1
__version__ = '0.0.1.%d' % __build__
__date__    = string.join(string.split('$Date: 2003-05-21 04:56:48 $')[1:3], ' ')
__author__  = 'Members of the ISU Game Developers Club <isugamedev-devel@lists.sourceforge.net>'
__doc__     = '''This is Barfight. For information regarding Barfight see:
    http://isugamedev.sourceforge.net'''
del string

import siren
from GameState import GameState


def registerState(stateClass, name):
   """
   Registers the state with the given class in the state factory with the given
   name.
   """
   class StateCreator(siren.StateCreator):
      def create(self):
         return stateClass()

   factory = siren.StateFactory.getInstance()
   factory.registerCreator(name, StateCreator())


# Register states with the state factory
#registerState(GameState, 'Game')
class GameStateCreator(siren.StateCreator):
   def create(self):
      return GameState()

creator = GameStateCreator()
siren.StateFactory.getInstance().registerCreator('Game', creator)

# Create the kernel and start it up
kernel = siren.Kernel()
kernel.start('Game')
