Midworld
http://isugamedev.sf.net

README File

Congratulations on downloaded the latest (probably broken) source to Midworld!
The following contains instructions on how to attempt to build our source code.
You will need the following external libraries:

Audiere	1.9.0		http://audiere.sourceforge.net
Corona	0.2.0 		http://corona.sourceforge.net
GLText	0.1.0		http://gltext.sourceforge.net
GMTL	0.1.8		http://ggt.sourceforge.net
Loom	0.0.2		http://ailoom.sourceforge.net
OpenSG	1.1.0		http://www.opensg.org
SCons	0.08		http://www.scons.org
SDL	1.2.4		http://www.libsdl.org

-Audiere-

Audiere is a sound library which can be obtained at
http://audiere.sourceforge.net

-Corona-

Corona is an image loading library which can be obtained at
http://corona.sourceforge.net

-GLText-

GLText is a TrueType font rendering library for OpenGL that uses FreeType2 as
the back end. It can be obtained from http://gltext.sourceforge.net

-GMTL-

GMTL is a Math library for graphical calculations.  It can be obtained from
http://ggt.sourceforge.net

-Loom-

Loom is a toolkit for rapid development of AI agents using a heirarchical
structure to create intelligent interactions between agents. Loom can be
obtained from http://ailoom.sourceforge.net

-OpenSG-

OpenSG is a scenegraph system for real-time rendering. It can be obtained from
http://www.opensg.org

-SCons-

SCons is a Python based build system.  To use Scons, you will need at least
Python 1.5.  Python can be obtained at http://www.python.org

-SDL-

SDL is a game library for drawing to the screen, taking input, etc.  It can be
obtained from http://www.libsdl.org


-Building Midworld-

Once you have built and installed the above libraries, you are ready to 
build Midworld.  This can be done from a shell with the following commands:

$ cd <midworld_root_directory>
$ ./get-resources.sh
$ scons

If all goes well, you should now be able to execute the game by changing to
the build directory and executing midworld.
 
$ cd build
$ ./midworld

Please feel free to email comments, questions, suggestions, etc to 
isugamedev-midworld@lists.sourceforge.net
