import os, sys

sys.path.append(os.getcwd())
from metropolis import *

class Character(Entity):
	"""
	Test Class
	"""
	def __init__(self, id):
		"""
		Ctor
		"""
		Entity.__init__(self, id)
		print self.getID()
		self.name = 'NoName'
		self.type = 'Character'
		self.race = 'NoRace'
		self.attributes = {'Body' : 0, 'Quickness' : 0, 'Strength' : 0, 'Charisma' : 0, 'Intelligence' : 0, 'Willpower' : 0, 'Essence' : 0, 'Magic' : 0, 'Reaction' : 0}
		self.skills = {}
		
	def update(self, dt):
		"""
		Updates this entity
		"""
	
	def getType(self):
		"""
		Returns the type of entity
		"""
		return 'Character'

	def printString(self):
		"""
		Dumps the data of this entity to the terminal
		"""
		print '===================== Entity Data ==========================='
		print 'ID : ' + str(self.getID())
		print self.type
		print self.name
		print self.race
		print self.attributes
		print self.skills
		print self.getPosition()
		print '============================================================='
	
e = Entity(5)
print e
print e.getID()
c = Character(10)
c.name = 'Daren'
c.race = 'Human'
c.attributes['Strength'] = 3
c.attributes['Body'] = 2
c.printString()
w = World.instance()
print w
w.addEntity(c)
