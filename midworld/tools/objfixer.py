#!/usr/bin/env python
############################################################## midworld-cpr beg
#
# midworld - retro post-nuclear mayhem
# midworld is (C) Copyright 2002 by
#    Chad Austin, Josh Brown, Johnathan Gurley,
#    Kevin Meinert, Andres Reinot, Ben Scott
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
# File:          $RCSfile: objfixer.py,v $
# Date modified: $Date: 2002-09-20 09:33:42 $
# Version:       $Revision: 1.1 $
# -----------------------------------------------------------------
############################################################## midworld-cpr end
import os, re, sys

#------------------------------------------------------------------------------
# This script takes an Wavefront OBJ file exported from 3DS Max R4 and fixes it
# up so that OpenSG will grok it without error.
#------------------------------------------------------------------------------

UNIT_CM  = 0.01
UNIT_M   = 1
UNIT_FT  = 0.304801

# Check if all the arguments have been specified
if len(sys.argv) < 3:
   print os.path.basename(sys.argv[0])+': Insufficient arguments'
   print 'Usage: '+os.path.basename(sys.argv[0])+' <source units> file+'
   sys.exit(1)

baseunit_opt = sys.argv[1]
if baseunit_opt == 'cm':
   baseunit = UNIT_CM
elif baseunit_opt == 'm':
   baseunit = UNIT_M
elif baseunit_opt == 'ft':
   baseunit = UNIT_FT
else:
   print 'Unknown base unit type: '+baseunit_opt
   sys.exit(1)


def scaleVertex(line, scale):
   """
   If the current line contains a vertex definition, scale it by the given
   value.
   """

   # Check if this line has a vertex
   matches = re.compile(r'^v +(-?\d+\.\d+) +(-?\d+\.\d+) +(-?\d+\.\d+)').match(line)
   if matches != None:
      x = float(matches.group(1)) * scale
      y = float(matches.group(2)) * scale
      z = float(matches.group(3)) * scale
      return 'v '+str(x)+' '+str(y)+' '+str(z)+'\n'
   else:
      return line

def remove3DTexCoord(line):
   """
   Strips off the 3rd texture coordinate from a texture coordinate definition in
   the given line if it exists. OpenSG doesn't seem to handle it very well.
   """

   # Check if this line defines a texture coord
   matches = re.compile(r'^vt +(-?\d+\.\d+) +(-?\d+\.\d+) +-?\d+\.\d+').match(line)
   if matches != None:
      u = float(matches.group(1))
      v = float(matches.group(2))
      return 'vt '+str(u)+' '+str(v)+'\n'
   else:
      return line

def fix(file):
   """
   Fixes the OBJ file in the current line so that it to load without errors in
   an OpenSG scenegraph.
   """
   global baseunit
   output = []

   # loop on the lines in the file
   for line in open(file, 'r').readlines():
      result = line
      result = scaleVertex(result, baseunit)
      result = remove3DTexCoord(result)
      output.append(result)

   # overwrite the file
   open(file, 'w').writelines(output)

# Run through each file and "fix" it
for file in sys.argv[2:]:
   fix(file)
