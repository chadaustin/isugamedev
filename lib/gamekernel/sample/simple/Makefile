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
# Date modified: $Date: 2002-02-20 03:03:00 $
# Version:       $Revision: 1.2 $
# -----------------------------------------------------------------
#
################## <GK heading END do not edit this line> ###################

# objects to be included in the project....
SRCS = main.cpp 

# project name...
PROJECT_NAME = simple

OBJDIR = .
DEPDIR =

PATH_TO_SRCS = .
MK_DIR = ../../mk
INCLUDE_PATHS = -I. -I../../ -I../../external/xdl

########################################################################
# system dependent stuff, that users will want to change...
# stuff that cant be abstracted in the build system...
##########################################################################
include ${MK_DIR}/mk.hosttype
include ${MK_DIR}/mk.platform

EXTRA = 

# IRIX
ifeq ($(HOSTTYPE), IRIX)
   LIBS = $(EXTRA) -lGLU -lGL -lglut -lX11 -lXmu -lm
   DEFS += -DUSE_UNIX
endif

#LiNUX
ifeq ($(HOSTTYPE), linux)
   LIBS = -L/usr/X11R6/lib -L../../ -lgk -lGLU -lGL -lglut -lX11 -lXmu -lm
   DEFS += -DUSE_UNIX
endif

# Win32
ifeq ($(HOSTTYPE), Win32)
   LIBS =
   DEPENDFLAGS = -D__cplusplus -D_WIN32 -DWIN32 $(INCLUDE_PATHS)
   DEFS += -DUSE_WIN32
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
