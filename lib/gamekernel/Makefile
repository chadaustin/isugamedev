################### <GK heading BEGIN do not edit this line> #################
#
# gamekernel - a platform for running games
# gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
#
# Authors: Kevin Meinert <kevin@vrsource.org>
#          Ben Scott <bscott@iastate.edu>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
# -----------------------------------------------------------------
# File:          $RCSfile: Makefile,v $
# Date modified: $Date: 2002-02-19 21:36:35 $
# Version:       $Revision: 1.15 $
# -----------------------------------------------------------------
#
################## <GK heading END do not edit this line> ###################

# objects to be included in the project....
gk_SRCS = \
   GameKernel.cpp \
	SystemDriverFactory.cpp \
   xmlparser.cpp  xmlpp.cpp  xmltokenizer.cpp

glut_SRCS = \
	GlutDriver.cpp

sdl_SRCS = \
	SdlDriver.cpp

OBJDIR = .
DEPDIR = 

PATH_TO_SRCS = ./gk:./xmlpp
MK_DIR = mk
INCLUDE_PATHS = -I. -I./external/xdl
DEFS ?=

DRIVERS = glut_driver sdl_driver

default: gk
	@echo
	@echo "-------------------------------------------"
	@echo "You just built the base GameKernel library."
	@echo "You must build your drivers seperately:"
	@echo " > gmake glut_driver"
	@echo " > gmake sdl_driver"
	@echo "-------------------------------------------"

gk:
	@echo "-------------------------------------------"
	@echo "Building base GameKernel library."
	@echo "-------------------------------------------"
	$(MAKE) SRCS='$(gk_SRCS)' PROJECT_NAME='gk' DO_DEPENDS=Y build

$(DRIVERS):
	@echo "-------------------------------------------"
	@echo "Building the $(@:%_driver=%) driver"
	@echo "-------------------------------------------"
	$(MAKE) SRCS='$($(@:%_driver=%)_SRCS)' PROJECT_NAME='$(@:%_driver=%)drv' DEFS='-DXDL_BUILD_DLL' DO_DEPENDS=Y build
#	$(MAKE) SRCS='$($(@:%_driver=%)_SRCS)' PROJECT_NAME='$(@:%_driver=%)drv' DO_DEPENDS=Y build


########################################################################
# system dependent stuff, that users will want to change...
# stuff that cant be abstracted in the build system...
##########################################################################
include ${MK_DIR}/mk.hosttype
include ${MK_DIR}/mk.platform

# IRIX
ifeq ($(HOSTTYPE), irix)
   LIBS = 
   override DEFS += -DUSE_UNIX
endif

#LiNUX
ifeq ($(HOSTTYPE), linux)
   LIBS = 
   override DEFS += -DUSE_UNIX
endif

# Win32
ifeq ($(HOSTTYPE), Win32)
   LIBS = 
   override DEFS += -DUSE_WIN32
endif
########################################################################

include ${MK_DIR}/mk.objs

# Compile then Link
build: $(OBJS)
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Linking... (.$(OBJ_FILE_SUFFIX)'s --> .so)"
	-@echo "-------------------------------------------"
	$(SO_LINKER) $(SO_FLAGS) $(OBJS) $(OUTPUT_LIB_FLAG)$(LIB_FILENAME) $(LIBS)
	$(STATIC_LINKER) $(STATIC_FLAGS) $(OUTPUT_STATIC_LIB_FLAG)$(STATIC_LIB_FILENAME) $(OBJS) 
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "$(FILENAME) done"
	-@echo "-------------------------------------------"

prefix ?= installed

install: build
	-mkdir $(prefix)
	-mkdir $(prefix)/include
	-mkdir $(prefix)/include/gk
	-mkdir $(prefix)/lib$(LIBBITSUF)
	-mkdir $(prefix)/share
	-mkdir $(prefix)/share/gk
	-cp gk/*.h $(prefix)/include/gk
	-cp $(LIB_FILENAME) $(STATIC_LIB_FILENAME) $(prefix)/lib$(LIBBITSUF)
	-cp data/* $(prefix)/share/gk

make_a_filename = $(addsuffix $(STATIC_LIB_FILE_SUFFIX), $(addprefix $(STATIC_LIB_FILE_PREFIX), $1))
make_so_filename = $(addsuffix $(LIB_FILE_SUFFIX), $(addprefix $(LIB_FILE_PREFIX), $1))


# Remove the compiled stuff from the system
clean:
	-@echo ""
	-@echo "-------------------------------------------"
	-@echo "Removing compiled stuff from the system	 "
	-@echo "-------------------------------------------"
	-rm -rf *.o $(STATIC_LIB_FILENAME) $(LIB_FILENAME) *.ncb *.opt *.plg *.ilk *.idb *.pdb *.pch Debug/ Release/ ii_files/ $(call make_so_filename, $(TARGETS)) $(call make_a_filename, $(TARGETS))

clobber: clean
	-rm -f *.d

ifdef DO_DEPENDS
   include ${MK_DIR}/mk.depend
endif

.PHONY: gk $(DRIVERS)
