#!gmake
# How to build?  Use gnu-make (type gmake)
# NOTE! some systems might not have gmake, only make.. 
#       IRIX, LiNUX, and Win32 has gmake available for sure.

# project name...
NAME = simple

# objects to be included in the project....
OBJS = simpleGlutApp.o cubeGeometry.o QuakeNav.o Matrix4f.o

vpath %.cxx ../../

# IRIX:
# your compiler and it's flags:
CXX = CC 
CXXFLAGS = -LANG:std -g -n32 -mips3 -all

# Linux
#CXX = g++
#CXXFLAGS = -g 
LIBBITSUF = 32
BE_VERBOSE = -Wl,-v 

# libraries needed for opengl and glut
GLUT_LIB_PATH = -L/home/users/kevn/software/${HOSTTYPE}/lib$(LIBBITSUF)
#X_LIB_PATH = -L/usr/X11R6/lib
GLIBS = $(GLUT_LIB_PATH) -lglut -lGLU -lGL -lXmu -lXext -lX11 -lXi 
LIBS = ${GLIBS} -lm

# search paths for glut
INCLUDEPATHS = -I.. -I../.. -I/home/users/kevn/software/${HOSTTYPE}/include
 
# the "default" make target...  
# depends on ${OBJS}, and then links them into an exe
default: ${OBJS}
	$(CXX) $(CXXFLAGS) ${OBJS} -o $(NAME) $(LIBS)

# Rules for compiling any sourcecode filetype into a .o
CREATE_OBJ_FILE = $(CXX) $(CXXFLAGS) -c $(WARNINGS) $(DEFS) $(INCLUDEPATHS) $< -o $@

%.o: %.c
	$(CREATE_OBJ_FILE)

%.o: %.cxx
	$(CREATE_OBJ_FILE)

%.o: %.c++
	$(CREATE_OBJ_FILE)

%.o: %.C
	$(CREATE_OBJ_FILE)

%.o: %.cpp
	$(CREATE_OBJ_FILE)

%.o: %.C
	$(CREATE_OBJ_FILE)

tarball: clean clobber
	./make-tarball.sh glutsimple src ${TARBALLPATH}

clobber: clean

# the "clean" target, cleans object code and exe from the directory...
# NOTE: SGI's CC command produces an ii_files directory.
clean:
	-rm -r $(OBJS) $(NAME) ii_files
