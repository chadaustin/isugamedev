#!gmake
# How to build?  Use gnu-make (type gmake)
# NOTE! some systems might not have gmake, only make.. 
#       IRIX, LiNUX, and Win32 has gmake available for sure.

# You'll need to edit this file .
# fill in the glut search paths, and uncomment the appropriate compiler.

# project name...
NAME = simple

# objects to be included in the project....
SRCS = simpleGlutApp.cxx Matrix4f.cxx Light.cxx ColorRGBA.cxx

include mk/mk.irix

# search paths for glut (modify this!)
LIBS = -lglut -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lX11 -lXi -lm
INCLUDE_PATHS = -I/home/users/kevn/software/${HOSTTYPE}/include
LIBPATHS = -L/home/users/kevn/software/${HOSTTYPE}/lib32
 
include mk/mk.objs

# the "default" make target...  
# depends on ${OBJS}, and then links them into an exe
default: ${OBJS}
	$(CC) $(CXX_FLAGS) $(INCLUDE_PATHS) ${OBJS} -o $(NAME) $(LIBPATHS) $(LIBS)




clobber: clean

# the "clean" target, cleans object code and exe from the directory...
# NOTE: SGI's CC command produces an ii_files directory.
clean:
	-rm -r $(OBJS) $(NAME) ii_files

include mk/mk.depend
