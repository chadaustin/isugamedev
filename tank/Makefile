
#!gmake
# How to build?  Use gnu-make (type gmake)

# You'll need to edit this file .
# fill in the glut search paths

# project name...
PROJECT_NAME = tank


# objects to be included in the project....
SRCS = \
   BmpImporter.cxx \
   ColorRGBA.cxx \
   CppImageExporter.cxx \
   Entity.cxx \
   FileHandler.cxx \
   Image.cxx \
   ImageManager.cxx \
   Light.cxx \
   Material.cxx \
   Matrix4f.cxx \
   simpleGlutApp.cxx \
   Texture.cxx \
   TgaImporter.cxx \
   World.cxx

MK_DIR = ./mk
PATH_TO_SRCS = .
INCLUDE_PATHS += -I./regexx

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
ifeq ($(HOSTTYPE), linux)
   INCLUDE_PATHS += -I/usr/X11R6/include
   LIBPATHS += -L/usr/X11R6/lib
endif
endif




include ${MK_DIR}/mk.objs

ifeq ($(HOSTTYPE), Win32)
   LIBS += .\\regexx\\regexx.lib Glut32.lib Glu32.lib OpenGL32.lib 
else
   LIBS += -L./regexx -lregexx -lglut -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lX11 -lXi -lm
endif

# the "default" make target...  
# depends on ${OBJS}, and then links them into an exe
default:
	$(MAKE) USE_DEPEND='Y' tank$(EXE_FILE_SUFFIX)

debug:
	$(MAKE) USE_DEBUG='Y' default

release:
	$(MAKE) USE_DEBUG='N' default

# rule to build the regexx library.
$(LIB_FILE_PREFIX)regexx.$(LIB_FILE_SUFFIX):
	cd regexx && $(MAKE)
	ln -s regexx/$(LIB_FILE_PREFIX)regexx.$(LIB_FILE_SUFFIX) .

tank$(EXE_FILE_SUFFIX): $(LIB_FILE_PREFIX)regexx.$(LIB_FILE_SUFFIX) \
                           ${OBJS} \
                           imageIoReg.$(OBJ_FILE_SUFFIX) 
	@echo " "
	@echo "----------------------"
	@echo "Making TANK executable"
	@echo "----------------------"
	@echo " "
	$(EXE_LINKER) $(EXE_FLAGS) ${OBJS} $(LINKALL_ON) imageIoReg.$(OBJ_FILE_SUFFIX) $(LINKALL_OFF) $(OUTPUT_EXE_FLAG)$(EXE_FILENAME) $(LIB_PATHS) $(LIBS)

clobber: clean
	rm -f *.d

# the "clean" target, cleans object code and exe from the directory...
# NOTE: SGI's CC command produces an ii_files directory.
clean:
	@echo " "
	@echo "================="
	@echo "Cleaning regexx"
	@echo "================="
	@echo " "
	cd regexx && $(MAKE) clean
	@echo " "
	@echo "================="
	@echo "Cleaning TANK"
	@echo "================="
	@echo " "
	-rm -rf $(OBJS) $(EXE_FILENAME) ii_files
	-rm $(LIB_FILE_PREFIX)regexx.$(LIB_FILE_SUFFIX)

ifeq ($(USE_DEPEND),Y)
include ${MK_DIR}/mk.depend
endif
