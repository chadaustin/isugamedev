############################################################## barfight-cpr beg
#
# barfight - an all-out brawl in the local pub
# barfight is (C) Copyright 2003 by members of the
#    Iowa State University Game Developers Club
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
# File:          $RCSfile: Util.py,v $
# Date modified: $Date: 2003-06-03 03:56:17 $
# Version:       $Revision: 1.1 $
# -----------------------------------------------------------------
############################################################## barfight-cpr end
import gmtl

def getMatrixData(matrix):
   """
   Gets a tuple containing the data withing the given matrix.
   """
   return (matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
           matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
           matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
           matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3])
