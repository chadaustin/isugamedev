#!/bin/sh

##############################################################################
# This script was originally written by
#     Patrick Hartling <patrick@vrac.iastate.edu>
#
# It has since been modified for use with the GameKernel project.
##############################################################################

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
# File:          $RCSfile: autogen.sh,v $
# Date modified: $Date: 2002-02-20 04:01:14 $
# Version:       $Revision: 1.1 $
# -----------------------------------------------------------------
#
################## <GK heading END do not edit this line> ###################

# Run this to generate all the initial makefiles

DIE=0

# check for autoconf
(autoconf --version) < /dev/null > /dev/null 2>&1 || {
   echo
   echo "**Error**: You must have \`autoconf' installed to compile GameKernel."
   echo "Download the approriate package for your distribution,"
   echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
   DIE=1
}

# check for aclocal
(aclocal --version) < /dev/null > /dev/null 2>&1 || {
   echo
   echo "**Error**: Missing \`aclocal'. The version of \`automake'"
   echo "installed doesn't appear to be recent enough."
   echo "Get ftp://ftp.gnu.org/pub/gnu/automake-1.4.tar.gz"
   echo "(or a newer version if it is available)"
   DIE=1
}

if test "$DIE" -eq 1; then
   exit 1
fi

# run aclocal
configdir=`sed -n -e 's,AC_CONFIG_AUX_DIR(\(.*\)),\1,gp' < configure.in`
if test "x$configdir" = "x"; then
   ACLOCAL_FLAGS=
else
   ACLOCAL_FLAGS="-I $configdir"
fi
echo "Running aclocal ${ACLOCAL_FLAGS}..."
aclocal $ACLOCAL_FLAGS

# run autoheader
if grep "^AC_CONFIG_HEADER" configure.in > /dev/null
then
   echo "Running autoheader..."
   autoheader
fi

# run autoconf
echo "Running autoconf..."
autoconf

