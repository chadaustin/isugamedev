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
# File:          $RCSfile: objbounds.py,v $
# Date modified: $Date: 2003-06-12 20:42:26 $
# Version:       $Revision: 1.2 $
# -----------------------------------------------------------------
############################################################## midworld-cpr end
import os, re, sys

#------------------------------------------------------------------------------
# This script takes an Wavefront OBJ file and determines its bounds.
#------------------------------------------------------------------------------

# Check if all the arguments have been specified
if len(sys.argv) < 2:
   print os.path.basename(sys.argv[0])+': Insufficient arguments'
   print 'Usage: '+os.path.basename(sys.argv[0])+' file+'
   sys.exit(1)


def calcBounds(file):
   """
   Gets the bounds of the OBJ in the current file
   """

   (xmin, ymin, zmin) = ( 1000000.0,  1000000.0,  1000000.0)
   (xmax, ymax, zmax) = (-1000000.0, -1000000.0, -1000000.0)

   # loop on the lines in the file
   for line in open(file, 'r').readlines():
      result = line
      matches = re.compile(r'v +(-?\d+\.\d+) +(-?\d+\.\d+) +(-?\d+\.\d+)').match(line)
      # Check if this is a vertex line
      if matches != None:
         x = float(matches.group(1))
         y = float(matches.group(2))
         z = float(matches.group(3))

         xmin = min(x, xmin)
         ymin = min(y, ymin)
         zmin = min(z, zmin)

         xmax = max(x, xmax)
         ymax = max(y, ymax)
         zmax = max(z, zmax)

   # Write out the corresponding XML
   xml = """   <model>
      <size xlo="%.1f" xhi="%.1f" ylo="%.1f" yhi="%.1f"/>
      <color r="1.0" g="0.0" b="0.0"/>
      <type name="%s"/>
   </model>
"""
   sys.stdout.write(xml % (xmin, xmax, zmin, zmax,
                           os.path.splitext(os.path.basename(file))[0]))

# Run through each file and calculate its bounds
print """<?xml version="1.0"?>"""
print """<level>"""
for file in sys.argv[1:]:
   calcBounds(file)
print """</level>"""
