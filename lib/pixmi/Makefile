# TODO: 
# - generate a library...
# - split this makefile into the proper subdirs
# - use configure.in for compile opts... (why???  make can do most of it)
#   - because we'd like to configure where zlib is (and other libs)
#

# project name...
PROJECT_NAME = pixmi
PROJECT_NAME1 = exSimple
PROJECT_NAME2 = exAdvanced
PROJECT_NAME3 = iconvert
PROJECT_NAME4 = iproperties

# objects to be included in the project....
zlib =  inflate.c deflate.c adler32.c trees.c zutil.c infblock.c inftrees.c infcodes.c infutil.c inffast.c
PNG_SRCS = PngImporter.cpp $(zlib) Crc32.cpp PngCRC.cpp
EXPORT_SRCS = BmpExporter.cpp SgiExporter.cpp CppImageExporter.cpp PcxExporter.cpp TgaExporter.cpp
IMPORT_SRCS = BmpImporter.cpp SgiImporter.cpp PcxImporter.cpp TgaImporter.cpp
IMAGEIO_SRCS = FileHandler.cpp Image.cpp
IMAGE_MANAGER_SRCS = ImageManager.cpp
IMAGE_SRCS = ${IMPORT_SRCS} $(EXPORT_SRCS) ${IMAGEIO_SRCS} ${IMAGE_MANAGER_SRCS} $(PNG_SRCS)
SRCS =  ${IMAGE_SRCS}

OBJDIR = .
DEPDIR = 

PATH_TO_SRCS = .:example:pixmi:zlib
MK_DIR = mk
INCLUDE_PATHS = -I. -Iexample -Imanager -Ipixmi -Izlib

########################################################################
# system dependent stuff, that users will want to change...
# stuff that cant be abstracted in the build system...
##########################################################################
include ${MK_DIR}/mk.platform
include ${MK_DIR}/mk.hosttype
# IRIX
ifeq ($(HOSTTYPE), irix)
   LIBS = -lpixmi
   include ${MK_DIR}/mk.irix
endif

#LiNUX
ifeq ($(HOSTTYPE), linux)
   LIBS = -lpixmi
   include ${MK_DIR}/mk.gnu
endif

# Win32
ifeq ($(HOSTTYPE), Win32)
   LIBS = pixmi.lib
   DEPENDFLAGS = -D__cplusplus -D_WIN32 -DWIN32 $(INCLUDE_PATHS)
   include ${MK_DIR}/mk.win32
   # Normal definitions
endif

########################################################################

include ${MK_DIR}/mk.objs

default: build

# Compile then Link
build: $(PROJECT_NAME1)$(OBJ_FILE_SUFFIX) $(PROJECT_NAME2)$(OBJ_FILE_SUFFIX) $(PROJECT_NAME3)$(OBJ_FILE_SUFFIX) $(PROJECT_NAME4)$(OBJ_FILE_SUFFIX) $(OBJS) 
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Linking... (.$(OBJ_FILE_SUFFIX)'s --> .so)"
	-@echo "-------------------------------------------"
	$(SO_LINKER) $(SO_FLAGS) $(OBJS) $(OUTPUT_LIB_FLAG)$(LIB_FILENAME) $(LIBS)
	$(STATIC_LINKER) $(STATIC_FLAGS) $(OUTPUT_STATIC_LIB_FLAG)$(STATIC_LIB_FILENAME) $(OBJS)
	$(EXE_LINKER) $(EXE_FLAGS) $(PROJECT_NAME1)$(OBJ_FILE_SUFFIX) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME1)$(EXE_FILE_SUFFIX) $(LIBS) $(LIBPATH).
	$(EXE_LINKER) $(EXE_FLAGS) $(PROJECT_NAME2)$(OBJ_FILE_SUFFIX) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME2)$(EXE_FILE_SUFFIX) $(LIBS) $(LIBPATH).
	$(EXE_LINKER) $(EXE_FLAGS) $(PROJECT_NAME3)$(OBJ_FILE_SUFFIX) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME3)$(EXE_FILE_SUFFIX) $(LIBS) $(LIBPATH).
	$(EXE_LINKER) $(EXE_FLAGS) $(PROJECT_NAME4)$(OBJ_FILE_SUFFIX) $(OUTPUT_EXE_FLAG)$(PROJECT_NAME4)$(EXE_FILE_SUFFIX) $(LIBS) $(LIBPATH).
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "$(FILENAME) done"
	-@echo "-------------------------------------------"

prefix ?= installed


install: build
	-mkdir $(prefix)
	-mkdir $(prefix)/include
	-mkdir $(prefix)/include/pixmi
	-mkdir $(prefix)/lib$(LIBBITSUF)
	-mkdir $(prefix)/share
	-mkdir $(prefix)/share/pixmi
	-cp pixmi/*.h $(prefix)/include/pixmi
	-cp $(LIB_FILENAME) $(STATIC_LIB_FILENAME) $(prefix)/lib$(LIBBITSUF)
	-cp data/* $(prefix)/share/pixmi


# Remove the compiled stuff from the system
clean:
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Removing compiled stuff from the system	 "
	-@echo "-------------------------------------------"
	-rm -r $(OBJS) \
	$(LIB_FILENAME) $(STATIC_LIB_FILENAME) \
	$(PROJECT_NAME1)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME2)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME3)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME4)$(EXE_FILE_SUFFIX)\
	$(PROJECT_NAME1)$(OBJ_FILE_SUFFIX)\
	$(PROJECT_NAME2)$(OBJ_FILE_SUFFIX)\
	$(PROJECT_NAME3)$(OBJ_FILE_SUFFIX)\
	$(PROJECT_NAME4)$(OBJ_FILE_SUFFIX)\
	 *.ncb *.opt *.plg *.pch *.idb *.pdb *.ilk Debug/ Release/ ii_files/


clobber: clean
	-rm *.d

-include ${MK_DIR}/mk.depend
