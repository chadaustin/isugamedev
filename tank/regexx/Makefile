# =============================================================================
# Basic template makefile for libraries.
# $Id: Makefile,v 1.14 2002-08-20 16:03:59 subatomic Exp $
#
# *** IMPORTANT NOTES -- READ THESE FIRST ***
#     1) This file _requires_ the use of GNU make (gmake).
# =============================================================================

DZR_BASE_DIR=	.

# Nothing but comments should come before this line.
default: all
OBJDIR=objs.$(HOSTTYPE).$(CXX)
DEPDIR=deps.$(HOSTTYPE).$(CXX)
LIBDIR=./lib$(LIBBITSUF).$(HOSTTYPE).$(CXX)
prefix = installed.$(HOSTTYPE).$(CXX)

INSTALLCMD=./install-sh

# -----------------------------------------------------------------------------
# Application-specific variable settings.  It is safe to modify these.
# -----------------------------------------------------------------------------

# The base name of the library that is built.  A value must be set for this!
# The platform-specific extensions for shared libraries and static libraries
# are appended below.
LIB_NAME=	regexx

# The directory where the source files for this library are located.
srcdir=  	regexx

# Compiler flags needed for this library.  They are used as follows:
#
#    DEBUG_APP         - If set to TRUE, this librar will be compiled with
#                        debugging symbols and no optimized symbols
#    OPTIM_APP         - If set to TRUE, this librar will be compiled with
#                        optimized symbols and no debugging symbols
#    EXTRA_INCLUDES    - Extra include paths (-I... options) for the compilers
#
DEBUG_APP=		FALSE
OPTIM_APP=		TRUE
EXTRA_INCLUDES=		-I.

# The list of all source files needed for this librar.  Based on this, a list
# of object files is put in $(OBJS) automatically.
SRCS = maketables.c get.c study.c pcre.c regexx.cpp split.cpp

# Extend this as necessary to find source files that are not in the current
# directory.  Set EXTRA_PATH_FOR_SOURCES to all the directories that you
# have sources in. (current dir is already included by default)
EXTRA_PATH_FOR_SOURCES=	.

# Additional files and directories besides the standard ones that need to be
# removed by the 'clean' target.
CLEAN_FILES=		
CLEAN_DIRS=		

# The following include line MUST COME BEFORE the targets for compiling the
# library.
#
# To build a library, include the following basic file:
#
#     dzr.lib.mk - An ordinary software library
#
include $(DZR_BASE_DIR)/mk/dzr.lib.mk

# -----------------------------------------------------------------------------
# Targets.
# -----------------------------------------------------------------------------
SHARED_LIB_FILENAME=$(LIBDIR)/$(SHLIB_PREFIX)$(LIB_NAME)$(SHLIB_EXT) 
STATIC_LIB_FILENAME=$(LIBDIR)/$(LIB_PREFIX)$(LIB_NAME)$(LIB_EXT)
all: $(SHARED_LIB_FILENAME) $(STATIC_LIB_FILENAME)

tests:
	-cd test && ${MAKE}

MAKE_THE_LIBDIR=	@if [ ! -d $(LIBDIR) ]; then mkdir $(LIBDIR) ; fi
# Target for the shared library to be built.
$(SHARED_LIB_FILENAME): $(OBJS)
	-$(MAKE_THE_LIBDIR)
	$(SHARED_LINK) $(SHARED_OUT)$@ $(OBJS)

# Target for the static library to be built.
$(STATIC_LIB_FILENAME): $(OBJS)
	-$(MAKE_THE_LIBDIR)
	$(STATIC_LINK) $(STATIC_OUT)$@ $(OBJS)

# TODO: edit this to install your files... 
#        - determine if you need all the dirs (bin, share, lib, include)
#        - append cp or install commands for your .h, lib files...
#        - prefix is your install path, edit it to specify the default
install: all tests
	-$(INSTALLCMD) -d $(prefix)
	-$(INSTALLCMD) -d $(prefix)/include
	-$(INSTALLCMD) -d $(prefix)/include/$(LIB_NAME)
	-$(INSTALLCMD) -d $(prefix)/lib$(LIBBITSUF)
	-$(INSTALLCMD) -d $(prefix)/share/$(LIB_NAME)
	-$(INSTALLCMD) -d $(prefix)/bin
	-cp $(LIB_NAME)/*.hh $(prefix)/include/$(LIB_NAME)
	-cp $(SHARED_LIB_FILENAME) $(STATIC_LIB_FILENAME) $(prefix)/lib$(LIBBITSUF)
	-cp test/testregexx $(prefix)/share/$(LIB_NAME)

CLOBBER_FILES += $(SHARED_LIB_FILENAME) $(STATIC_LIB_FILENAME)
