"""
Figure out what libraries we need to link with to use OpenGL.
Defines OPENGL_LIBS.

Supported platforms:
  Cygwin
  Linux
  IRIX
"""



import sys
import string

# CYGWIN
if sys.platform == 'cygwin':
    OPENGL_LIBS = ['opengl32', 'glu32']

# IRIX
elif string.find(sys.platform, 'irix') != -1:
    OPENGL_LIBS = ['GLU', 'GL', 'X11', 'Xmu']

# GENERIC (LINUX?)
else:
    OPENGL_LIBS = ['GLU', 'GL']
