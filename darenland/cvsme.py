import os, sys, shutil
pj = os.path.join

def CVSme(dir):
	for x in os.listdir(dir):
		os.system('cvs add ' + pj(dir, x))
		if os.path.isdir(pj(dir, x)) and x != 'CVS':
			CVSme(pj(dir, x))
CVSme('./')
