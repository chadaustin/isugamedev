
################### <MK heading BEGIN do not edit this line> #################
#
# mk build system - really simple build system using GNU make
# mk is (C) Copyright 2001-2002 by Kevin Meinert, Patrick Hartling
#
# Authors: Kevin Meinert <kevin@vrsource.org>
#          Patrick Hartling <patrick@vrac.iastate.edu>
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
# File:          $RCSfile: mk.gnu,v $
# Date modified: $Date: 2002-01-31 02:32:21 $
# Version:       $Revision: 1.2 $
# -----------------------------------------------------------------
#
################## <MK heading END do not edit this line> ###################
ifeq ($(USE_DEBUG), Y)
DEBUG_FLAGS = -g
endif


# gnu compiler defines 
CC = g++
WARNINGS_FLAGS = 
CXX_COMPILE = g++
CXX_STATIC_FLAGS = $(DEBUG_FLAGS) $(WARNINGS_FLAGS)
CXX_SHARED_FLAGS = $(DEBUG_FLAGS) -fPIC $(WARNINGS_FLAGS)
CXX_FLAGS = $(CXX_STATIC_FLAGS)
C_COMPILE = gcc
C_FLAGS = $(CXX_FLAGS)
EXE_LINKER = $(CXX_COMPILE)
EXE_FLAGS = $(CXX_FLAGS) $(WARNINGS_FLAGS)
SO_LINKER = $(CXX_COMPILE)
SO_FLAGS = -shared -fPIC $(DEBUG_FLAGS) $(WARNINGS_FLAGS)
STATIC_LINKER = ar
STATIC_FLAGS = -ruv
DEFS =
LIBBITSUF=

LINKALL_ON = -Wl,--whole-archive
LINKALL_OFF = -Wl,--no-whole-archive

OBJ_FILE_SUFFIX = .o
EXE_FILE_SUFFIX =
LIB_FILE_PREFIX = lib
LIB_FILE_SUFFIX = .so
STATIC_LIB_FILE_PREFIX=lib
STATIC_LIB_FILE_SUFFIX=.a

EXE_FILENAME = $(PROJECT_NAME)
LIB_FILENAME = $(LIB_FILE_PREFIX)$(PROJECT_NAME)$(LIB_FILE_SUFFIX)
STATIC_LIB_FILENAME = $(LIB_FILE_PREFIX)$(PROJECT_NAME)$(STATIC_LIB_FILE_SUFFIX)

OUTPUT_EXE_FLAG = -o
OUTPUT_OBJ_FLAG = -c -o
OUTPUT_LIB_FLAG = -o
OUTPUT_STATIC_LIB_FLAG =
