Midworld
http://isugamedev.sf.net

README File

Congratulations on downloaded the latest (probably broken) source to Midworld!
The following contains instructions on how to attempt to build our source code.
You will need the following external libraries:

SCons	0.07		http://www.scons.org
GMTL	0.1.8		http://ggt.sourceforge.net
Corona	0.2.0 		http://corona.sourceforge.net
Audiere	1.0.4		http://audiere.sourceforge.net
SDL	1.2.4		http://www.libsdl.org
GLText	0.1.0		http://gltext.sourceforge.net

-Scons-

SCons is a Python based build system.  To use Scons, you will need at least
Python 1.5.  Python can be obtained at http://www.python.org

-GMTL-

GMTL is a Math library for graphical calculations.  It can be obtained from
http://ggt.sourceforge.net

-Corona-

Corona is an image loading library which can be obtained at
http://corona.sourceforge.net

-Audiere-

Audiere is a sound library which can be obtained at
http://audiere.sourceforge.net

-SDL-

SDL is a game library for drawing to the screen, taking input, etc.  It can be
obtained from http://www.libsdl.org

-GLText-

GLText is a TrueType font rendering library for OpenGL that uses FreeType2 as
the back end. It can be obtained from http://gltext.sourceforge.net


-Building Midworld-

Once you have built and installed the above libraries, you are ready to 
build Midworld.  This can be done from a shell with the following commands:

$ cd <midworld_root_directory>
$ scons

If all goes well, you should now be able to execute the game by changing to
the src directory and executing midworld.
 
$ cd src
$ ./midworld

Please feel free to email comments, questions, suggestions, etc to 
isugamedev-midworld@lists.sourceforge.net
