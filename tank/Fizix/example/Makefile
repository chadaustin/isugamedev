
#!gmake
# How to build?  Use gnu-make (type gmake)

# You'll need to edit this file .
# fill in the glut search paths

# project name...
PROJECT_NAME = e


# objects to be included in the project....
SRCS = simpleGlutApp.cxx cubeGeometry.cpp QuakeNav.cxx Matrix4f.cxx

MK_DIR = ../../mk
PATH_TO_SRCS = .:../../Fizix:../../
INCLUDE_PATHS += -I. -I../../ -I../../Fizix -I../../Fizix/operators
INCLUDE_PATHS += -I../../Fizix/system -I../../boost
INCLUDE_PATHS += -I../../boost/boost/compatibility/cpp_c_headers


include ${MK_DIR}/mk.hosttype
include ${MK_DIR}/mk.platform


WHOAMI:=$(shell whoami)
ifeq ($(WHOAMI), kevn)
ifneq ($(HOSTTYPE), Win32)
   INCLUDE_PATHS += -I/home/users/kevn/software/${HOSTTYPE}/include
   LIB_PATHS += -L/home/users/kevn/software/${HOSTTYPE}/lib32
endif
endif

ifeq ($(WHOAMI), bscott)
   INCLUDE_PATHS += -I/home/users/kevn/software/${HOSTTYPE}/include
   LIB_PATHS += -L/home/users/kevn/software/${HOSTTYPE}/lib32
ifeq ($(HOSTTYPE), linux)
   INCLUDE_PATHS += -I/usr/X11R6/include
   LIBPATHS += -L/usr/X11R6/lib
endif
endif


include ${MK_DIR}/mk.objs

ifeq ($(HOSTTYPE), Win32)
   LIBS += Glut32.lib Glu32.lib OpenGL32.lib 
else
   LIBS += -lglut -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lX11 -lXi -lm
endif

# the "default" make target...  
# depends on ${OBJS}, and then links them into an exe
default:
	$(MAKE) $(EXE_FILENAME)

vjtank:
	$(MAKE) VRJUGGLER='Y' default

debug:
	$(MAKE) USE_DEBUG='Y' default

release:
	$(MAKE) USE_DEBUG='N' default

$(EXE_FILENAME): do_tank

do_tank:
	@echo " "
	@echo "======================="
	@echo "Building example     "
	@echo "======================="
	@echo " "
	$(MAKE) USE_DEPEND='Y' USE_DEBUG=$(USE_DEBUG) build_tank
	@echo " "
	@echo "======================="
	@echo "Done building spacetank"
	@echo "======================="
	@echo " "

build_tank: ${OBJS}
	@echo "  "
	@echo "----------------------"
	@echo "Making $(EXE_FILENAME)"
	@echo "----------------------"
	@echo " "
	$(EXE_LINKER) $(EXE_FLAGS) ${OBJS} $(OUTPUT_EXE_FLAG)$(EXE_FILENAME) $(LIB_PATHS) $(LIBS)


clobber: clean
	rm -f *.d
	-rm *.ilk *.pdb *.opt *.idb *.pch *.lib *.exp

# the "clean" target, cleans object code and exe from the directory...
# NOTE: SGI's CC command produces an ii_files directory.
clean:
	@echo " "
	@echo "================="
	@echo "Cleaning $(PROJECT_NAME)"
	@echo "================="
	@echo " "
	-rm -rf $(OBJS) $(EXE_FILENAME) ii_files

ifeq ($(USE_DEPEND),Y)
include ${MK_DIR}/mk.depend
endif
