#!/bin/sh

################### <GK heading BEGIN do not edit this line> #################
#
# gamekernel - a platform for running games
# gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
#
# Authors: Kevin Meinert <kevin@vrsource.org>
#          Ben Scott <bscott@iastate.edu>
#
# This library is free software; you can redistribute it and#or
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
# File:          $RCSfile: makever.sh,v $
# Date modified: $Date: 2002-02-21 05:13:43 $
# Version:       $Revision: 1.1 $
# -----------------------------------------------------------------
#
################## <GK heading END do not edit this line> ###################

version_file="`pwd`/VERSION"
num_files=0
declare -a files

# Process arguments
while [ $# -gt 0 ]; do
   case $1 in
      # argument is an option
      --*)
         arg=`echo $1 | sed -e 's/^\(--[0-9A-Za-z][0-9A-Za-z\-]*\)=.*/\1/'`
         val=`echo $1 | sed -e 's/^--[0-9A-Za-z][0-9A-Za-z\-]*=\(.*\)/\1/'`
         shift
         case $arg in
            --version-file)
               version_file=$val
               ;;
            --help)
               echo "Usage: $0 [options] file+"
               echo "   --help                  display this help message"
               echo "   --version-file=file     use file as the VERSION file"
               exit 0
               ;;
            *)
               echo "ERROR: Unknown argument '$1'"
               echo "Use $0 --help"
               exit 1
               ;;
         esac
         ;;
      # argument is not an option
      *)
         files[$num_files]=$1
         num_files=$num_files+1
         shift
         ;;
   esac
done

# Make sure we got at least one file
if test ${#files[@]} = 0; then
   echo "ERROR: No files specified"
   echo "Use $0 --help"
   exit 1
fi

# Figure out the current date
date=`date '+%Y%m%d_%H%M%S'`

# Get the version info from the version file
if [ ! -r "$version_file" ]; then
   echo "ERROR: Could not read $version_file"
   exit 1
fi
ver_line=`head -1 $version_file`
version=`echo $ver_line | sed -e 's/^\(.*\) @.*/\1/'`

# Extract major, minor and patch numbers from the version
version_major=`echo $version | sed -e 's/^\([0-9][0-9]*\)\..*/\1/'`
version_minor=`echo $version | sed -e 's/^.*\.\([0-9][0-9]*\)\..*/\1/'`
version_patch=`echo $version | sed -e 's/^.*\.\([0-9][0-9]*\)$/\1/'`

# Make the build version off the date
version_build="$date"

# Process each file in turn
for file in ${files[@]}; do
   # Make sure we can read the file
   if [ ! -r "$file" ]; then
      echo "ERROR: Could not read $file"
      exit 1;
   fi

   out_file=`echo $file | sed -e 's/\(.*\)\.in/\1/'`

   # Process the file and send it to a temporary output
   cat $file | sed -e "s/@VERSION_MAJOR@/$version_major/" \
                   -e "s/@VERSION_MINOR@/$version_minor/" \
                   -e "s/@VERSION_PATCH@/$version_patch/" \
                   -e "s/@VERSION_BUILD@/$version_build/" \
             > "${out_file}.temp"

   # Only overwrite the output file if nothing changed
   if [ -r "${out_file}" ]; then
      if cmp -s "${out_file}" "${out_file}.temp"; then
         echo "${out_file} is unchanged"
         rm -f "${out_file}.temp"
      else
         mv -f "${out_file}.temp" "${out_file}"
      fi
   else
      mv -f "${out_file}.temp" "${out_file}"
   fi
done
