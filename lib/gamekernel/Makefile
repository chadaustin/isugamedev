# objects to be included in the project....
SRCS = aki.cpp GameKernel.cpp GlutDriver.cpp

# project name...
PROJECT_NAME = aki

OBJDIR = .
DEPDIR =

PATH_TO_SRCS = .
MK_DIR = mk
INCLUDE_PATHS = -I. -I/home/users/kevn/software/irix/include

########################################################################
# system dependent stuff, that users will want to change...
# stuff that cant be abstracted in the build system...
##########################################################################
include ${MK_DIR}/mk.platform
include ${MK_DIR}/mk.hosttype

EXTRA = -L/home/users/kevn/software/irix/lib32

# IRIX
ifeq ($(HOSTTYPE), IRIX)
   LIBS = -L/usr/X11R6/lib $(EXTRA) -lGLU -lGL -lglut -lX11 -lXmu -lm
   include ${MK_DIR}/mk.irix
endif

#LiNUX
ifeq ($(HOSTTYPE), linux)
   LIBS = -L/usr/X11R6/lib -lGLU -lGL -lglut -lX11 -lXmu -lm
   include ${MK_DIR}/mk.gnu
endif

# Win32
ifeq ($(HOSTTYPE), Win32)
   LIBS =
   DEPENDFLAGS = -D__cplusplus -D_WIN32 -DWIN32 $(INCLUDE_PATHS)
   include ${MK_DIR}/mk.win32
endif

# gnu2
ifeq ($(HOSTTYPE), GNU)
   LIBS = -L/usr/X11R6/lib -lGLU -lGL -lglut -lX11 -lXmu -lm
   include ${MK_DIR}/mk.gnu
endif
########################################################################

include ${MK_DIR}/mk.objs

# Compile then Link
build: $(OBJS)
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Linking... (.$(OBJ_FILE_SUFFIX)'s --> .so)"
	-@echo "-------------------------------------------"
	$(EXE_LINKER) $(EXE_FLAGS) $(OBJS) $(OUTPUT_EXE_FLAG)$(EXE_FILENAME) $(LIBS)
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "$(EXE_FILENAME) done"
	-@echo "-------------------------------------------"

# Remove the compiled stuff from the system
clean:
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Removing compiled stuff from the system	 "
	-@echo "-------------------------------------------"
	-rm -r $(OBJS) $(EXE_FILENAME) *.ncb *.opt *.plg *.ilk *.idb *.pdb *.pch Debug/ Release/ ii_files/



clobber: clean
	-rm *.d

include ${MK_DIR}/mk.depend
