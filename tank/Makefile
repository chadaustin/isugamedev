#!gmake
# How to build?  Use gnu-make (type gmake)

# You'll need to edit this file .
# fill in the glut search paths, and uncomment the appropriate compiler.

# project name...
PROJECT_NAME = simple

# objects to be included in the project....
SRCS = simpleGlutApp.cxx Matrix4f.cxx Light.cxx ColorRGBA.cxx
MK_DIR = ./mk
PATH_TO_SRCS = .

include ${MK_DIR}/mk.hosttype
include ${MK_DIR}/mk.platform

# search paths for glut (modify this!)
LIBS = -lglut -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lX11 -lXi -lm
#INCLUDE_PATHS = -I/home/users/kevn/software/${HOSTTYPE}/include
#LIBPATHS = -L/home/users/kevn/software/${HOSTTYPE}/lib32
 
include ${MK_DIR}/mk.objs

# the "default" make target...  
# depends on ${OBJS}, and then links them into an exe
default: ${OBJS}
	$(CC) $(CXX_FLAGS) $(INCLUDE_PATHS) ${OBJS} $(OUTPUT_EXE_FLAG) $(FILENAME) $(LIBPATHS) $(LIBS)




clobber: clean

# the "clean" target, cleans object code and exe from the directory...
# NOTE: SGI's CC command produces an ii_files directory.
clean:
	-rm -r $(OBJS) $(FILENAME) ii_files

include ${MK_DIR}/mk.depend
