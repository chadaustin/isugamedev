dnl ---------------------------------------------------------------------------
dnl This file has been modified to work with the GameKernel.
dnl
dnl Ben Scott <bscott@iastate.edu>
dnl ---------------------------------------------------------------------------

dnl ************ <auto-copyright.pl BEGIN do not edit this line> ************
dnl
dnl VR Juggler is (C) Copyright 1998, 1999, 2000 by Iowa State University
dnl
dnl Original Authors:
dnl   Allen Bierbaum, Christopher Just,
dnl   Patrick Hartling, Kevin Meinert,
dnl   Carolina Cruz-Neira, Albert Baker
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Library General Public
dnl License as published by the Free Software Foundation; either
dnl version 2 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Library General Public License for more details.
dnl
dnl You should have received a copy of the GNU Library General Public
dnl License along with this library; if not, write to the
dnl Free Software Foundation, Inc., 59 Temple Place - Suite 330,
dnl Boston, MA 02111-1307, USA.
dnl
dnl -----------------------------------------------------------------
dnl File:          $RCSfile: misc.m4,v $
dnl Date modified: $Date: 2002-02-20 04:01:14 $
dnl Version:       $Revision: 1.1 $
dnl -----------------------------------------------------------------
dnl
dnl ************* <auto-copyright.pl END do not edit this line> *************

dnl ----------------------------------------------------------------------------
dnl Usage:
dnl   GK_VERSION_GROK(version-file)
dnl ----------------------------------------------------------------------------
AC_DEFUN(GK_VERSION_GROK,
[
   version_file="$srcdir/$1"

   MAJOR_VERSION=0
   MINOR_VERSION=0
   PATCH_VERSION=0

   if test -r "$version_file"; then
      ver_str=`head -1 "$version_file"`
      ver_num=`echo "$ver_str" | sed -e 's/^\(.*\) @.*@$/\1/'`
      ver_str_sep=`echo "$ver_num" | sed -e 's/\./ /g'`
      MAJOR_VERSION=`echo "$ver_str_sep" | sed -e 's/^\(..*\) ..* ..*$/\1/'`
      MINOR_VERSION=`echo "$ver_str_sep" | sed -e 's/^..* \(..*\) ..*$/\1/'`
      PATCH_VERSION=`echo "$ver_str_sep" | sed -e 's/^..* ..* \(..*\)$/\1/'`
   fi

   AC_SUBST(MAJOR_VERSION)
   AC_SUBST(MINOR_VERSION)
   AC_SUBST(PATCH_VERSION)
])
