
#!gmake
# How to build?  Use gnu-make (type gmake)

# You'll need to edit this file .
# fill in the glut search paths

# project name...
PROJECT_NAME = tank


# objects to be included in the project....
SRCS = \
   AudioSystemFactory.cxx \
   BmpImporter.cxx \
   ColorRGBA.cxx \
   CppImageExporter.cxx \
   Entity.cxx \
   FileHandler.cxx \
   Geode.cxx \
   GeodeCache.cxx \
   glRenderLight.cxx \
   Image.cxx \
   ImageManager.cxx \
   iniFile.cxx \
   Light.cxx \
   Material.cxx \
   Matrix4f.cxx \
   NullAudioSystem.cxx \
   Player.cxx \
   TankGame.cxx \
   Texture.cxx \
   TgaImporter.cxx \
   cubeGeometry.cxx \
   World.cxx

MK_DIR = ./mk
PATH_TO_SRCS = .:Fizix/example
INCLUDE_PATHS += -I. -I./boost -I./regexx -I./boost/boost/compatibility/cpp_c_headers/

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

ifeq ($(VRJUGGLER),Y)
   INCLUDE_PATHS += -I$(VJ_BASE_DIR)/include
   LIBPATHS += -B dynamic -L$(VJ_BASE_DIR)/lib32
   LIBS += -lJuggler -lJuggler_utils -lJuggler_ogl \
           -Wl,-rpath,$(VJ_BASE_DIR)/lib32
   SRCS += sys_juggler.cxx
else
   SRCS += sys_glut.cxx
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
	$(MAKE) tank$(EXE_FILE_SUFFIX)

vjtank:
	$(MAKE) VRJUGGLER='Y' default

debug:
	$(MAKE) USE_DEBUG='Y' default

release:
	$(MAKE) USE_DEBUG='N' default

# rule to build the regexx library.
regexx/$(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX):
	@echo "----------------------------------------"
	@echo "Regexx lib not found, making it first..."
	@echo "----------------------------------------"
	cd regexx && $(MAKE)

# make sure we have access to the regexx lib (through a symlink)
$(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX): regexx/$(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX)
	@echo "-------------------------------------------------------"
	@echo "Making symlink to regexx/$(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX) in local directory"
	@echo "-------------------------------------------------------"
	ln -s regexx/$(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX) .

tank$(EXE_FILE_SUFFIX): $(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX) do_tank

do_tank:
	@echo " "
	@echo "======================="
	@echo "Building spacetank     "
	@echo "======================="
	@echo " "
	$(MAKE) VRJUGGLER=$(VRJUGGLER) USE_DEPEND='Y' USE_DEBUG=$(USE_DEBUG) build_tank
	@echo " "
	@echo "======================="
	@echo "Done building spacetank"
	@echo "======================="
	@echo " "

build_tank: ${OBJS} imageIoReg$(OBJ_FILE_SUFFIX) 
	@echo "  "
	@echo "----------------------"
	@echo "Making $(EXE_FILENAME)"
	@echo "----------------------"
	@echo " "
	$(EXE_LINKER) $(EXE_FLAGS) ${OBJS} $(LINKALL_ON) imageIoReg$(OBJ_FILE_SUFFIX) $(LINKALL_OFF) $(OUTPUT_EXE_FLAG)$(EXE_FILENAME) $(LIB_PATHS) $(LIBS)


clobber: clean
	rm -f *.d
	-rm *.ilk *.pdb *.opt *.idb *.pch *.lib *.exp

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
	-rm -rf $(OBJS) $(EXE_FILENAME) ii_files imageIoReg$(OBJ_FILE_SUFFIX)
	-rm $(LIB_FILE_PREFIX)regexx$(LIB_FILE_SUFFIX)

ifeq ($(USE_DEPEND),Y)
include ${MK_DIR}/mk.depend
endif
