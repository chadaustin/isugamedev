# TODO: 
# - generate a library...
# - split this makefile into the proper subdirs
# - use configure.in for compile opts... (why???  make can do most of it)
#   - because we'd like to configure where zlib is (and other libs)
#

# project name...
PROJECT_NAME1 = exSimple
PROJECT_NAME2 = exAdvanced
PROJECT_NAME3 = iconvert
PROJECT_NAME4 = iproperties
PROJECT_NAME5 = png

# objects to be included in the project....
zlib =  inflate.c deflate.c adler32.c trees.c zutil.c infblock.c inftrees.c infcodes.c infutil.c inffast.c
PNG_SRCS = PngImporter.cpp $(zlib) Crc32.cpp PngCRC.cpp
EXPORT_SRCS = BmpExporter.cpp SgiExporter.cpp CppImageExporter.cpp PcxExporter.cpp TgaExporter.cpp
IMPORT_SRCS = BmpImporter.cpp SgiImporter.cpp PcxImporter.cpp TgaImporter.cpp
IMAGEIO_SRCS = FileHandler.cpp Image.cpp
IMAGE_MANAGER_SRCS = ImageManager.cpp
IMAGE_SRCS = ${IMPORT_SRCS} $(EXPORT_SRCS) ${IMAGEIO_SRCS} ${IMAGE_MANAGER_SRCS} $(PNG_SRCS)
SRCS1 = exSimple.cpp ${IMAGE_SRCS}
SRCS2 = exAdvanced.cpp ${IMAGE_SRCS}
SRCS3 = iconvert.cpp ${IMAGE_SRCS}
SRCS4 = iproperties.cpp ${IMAGE_SRCS}

OBJDIR = .
DEPDIR = 

PATH_TO_SRCS = .:example:pixmi:zlib
MK_DIR = mk
INCLUDE_PATHS = -I. -Iexample -Ipixmi -Izlib

########################################################################
# system dependent stuff, that users will want to change...
# stuff that cant be abstracted in the build system...
##########################################################################
include ${MK_DIR}/mk.platform
include ${MK_DIR}/mk.hosttype
# IRIX
ifeq ($(HOSTTYPE), IRIX)
   LIBS = -lm 
   include ${MK_DIR}/mk.irix
endif

#LiNUX
ifeq ($(HOSTTYPE), Linux)
   LIBS = -lm 
   include ${MK_DIR}/mk.gnu
endif

# Win32
ifeq ($(HOSTTYPE), Win32)
   LIBS = 
   DEPENDFLAGS = -D__cplusplus -D_WIN32 -DWIN32 $(INCLUDE_PATHS)
   include ${MK_DIR}/mk.win32
   # Normal definitions
endif

# gnu2
ifeq ($(HOSTTYPE), GNU)
   INCLUDE_PATHS =  -I. -Iexample -Imanager -IUtils -Izlib
   LIBS = -lm
   include ${MK_DIR}/mk.gnu
endif
########################################################################

include ${MK_DIR}/mk.objs

# add a directory prefix to each source file
# OBJS := ${addprefix ${OBJDIR}/,$(SRCS)}
# Construct $(OBJS) from $(SRCS) using the makeobjs function.
OBJS1 = $(call makeobjs, $(SRCS1))
OBJS2 = $(call makeobjs, $(SRCS2))
OBJS3 = $(call makeobjs, $(SRCS3))
OBJS4 = $(call makeobjs, $(SRCS4))
OBJS = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)

# Compile then Link
build: $(OBJS)
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Linking... (.$(OBJ_FILE_SUFFIX)'s --> .so)"
	-@echo "-------------------------------------------"
	$(EXE_LINKER) $(EXE_FLAGS) $(OBJS1) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME1)$(EXE_FILE_SUFFIX) $(LIBS)
	$(EXE_LINKER) $(EXE_FLAGS) $(OBJS2) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME2)$(EXE_FILE_SUFFIX) $(LIBS)
	$(EXE_LINKER) $(EXE_FLAGS) $(OBJS3) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME3)$(EXE_FILE_SUFFIX) $(LIBS)
	$(EXE_LINKER) $(EXE_FLAGS) $(OBJS4) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME4)$(EXE_FILE_SUFFIX) $(LIBS)
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "$(FILENAME) done"
	-@echo "-------------------------------------------"

# Remove the compiled stuff from the system
clean:
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Removing compiled stuff from the system	 "
	-@echo "-------------------------------------------"
	-rm -r $(OBJS) \
	$(PROJECT_NAME1)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME2)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME3)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME4)$(EXE_FILE_SUFFIX)\
	 *.ncb *.opt *.plg *.pch *.idb *.pdb *.ilk Debug/ Release/ ii_files/


clobber: clean
	-rm *.d

-include ${MK_DIR}/mk.depend
