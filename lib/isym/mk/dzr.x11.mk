# ************** <auto-copyright.pl BEGIN do not edit this line> **************
# Doozer
#
# Original Authors:
#   Patrick Hartling, Kevin Meinert
# -----------------------------------------------------------------------------
# VR Juggler is (C) Copyright 1998, 1999, 2000, 2001 by Iowa State University
#
# Original Authors:
#   Allen Bierbaum, Christopher Just,
#   Patrick Hartling, Kevin Meinert,
#   Carolina Cruz-Neira, Albert Baker
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
# File:          $RCSfile: dzr.x11.mk,v $
# Date modified: $Date: 2002-06-28 22:59:54 $
# Version:       $Revision: 1.1.1.1 $
# -----------------------------------------------------------------
# *************** <auto-copyright.pl END do not edit this line> ***************

# -----------------------------------------------------------------------------
#
# $Id: dzr.x11.mk,v 1.1.1.1 2002-06-28 22:59:54 subatomic Exp $
# -----------------------------------------------------------------------------

include $(DZR_BASE_DIR)/mk/dzr.hosttype.mk

ifeq ($(HOSTTYPE), IRIX)
X11_LDFLAGS?=	
X11_LIBS?= 	-lX11 -lXext
endif
ifeq ($(HOSTTYPE), Linux)
X11_LDFLAGS?=	-L/usr/X11R6/lib
X11_LIBS?= 	-lX11 -lXext
endif
ifeq ($(HOSTTYPE), FreeBSD)
X11_LDFLAGS?=	-L/usr/X11R6/lib
X11_LIBS?= 	-lX11 -lXext
endif
