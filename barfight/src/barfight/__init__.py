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
# File:          $RCSfile: __init__.py,v $
# Date modified: $Date: 2003-06-02 17:38:46 $
# Version:       $Revision: 1.2 $
# -----------------------------------------------------------------
############################################################## barfight-cpr end
import string
__build__   = 1
__version__ = '0.0.1.%d' % __build__
__date__    = string.join(string.split('$Date: 2003-06-02 17:38:46 $')[1:3], ' ')
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
