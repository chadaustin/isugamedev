#!gmake
# How to build?  Use gnu-make (type gmake)

# You'll need to edit this file .
# fill in the glut search paths, and uncomment the appropriate compiler.

# project name...
PROJECT_NAME = tank

# objects to be included in the project....
SRCS = ImageManager.cxx FileHandler.cxx simpleGlutApp.cxx Matrix4f.cxx Light.cxx \
       ColorRGBA.cxx Material.cxx Texture.cxx TgaImporter.cxx Image.cxx \
       CppImageExporter.cxx BmpImporter.cxx imageIoReg.cxx
MK_DIR = ./mk
PATH_TO_SRCS = .

include ${MK_DIR}/mk.hosttype
include ${MK_DIR}/mk.platform


WHOAMI:=$(shell whoami)
ifeq ($(WHOAMI), kevn)
ifneq ($(HOSTTYPE), Win32)
   INCLUDE_PATHS += -I/home/users/kevn/software/${HOSTTYPE}/include
   LIBPATHS += -L/home/users/kevn/software/${HOSTTYPE}/lib32
endif
endif




include ${MK_DIR}/mk.objs

ifeq ($(HOSTTYPE), Win32)
   LIBS=Glut32.lib Glu32.lib OpenGL32.lib 
else
   LIBS = -lglut -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lX11 -lXi -lm
endif

# the "default" make target...  
# depends on ${OBJS}, and then links them into an exe
default: ${OBJS}
	$(EXE_LINKER) $(EXE_FLAGS) ${OBJS} $(OUTPUT_EXE_FLAG)$(FILENAME) $(LIBPATHS) $(LIBS)




clobber: clean
	rm *.d

# the "clean" target, cleans object code and exe from the directory...
# NOTE: SGI's CC command produces an ii_files directory.
clean:
	-rm -r $(OBJS) $(FILENAME) ii_files

include ${MK_DIR}/mk.depend
