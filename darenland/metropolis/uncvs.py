import os, sys, shutil
pj = os.path.join

def rmCVS(dir):
	for x in os.listdir(dir):
		if x == 'CVS':
			shutil.rmtree(pj(dir, x))
		elif os.path.isdir(pj(dir, x)):
			rmCVS(pj(dir, x))
		else:
			x = 'do nothing'

rmCVS(os.getcwd())
