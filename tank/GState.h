
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     graphics state     =-
//
// Description: "state information.  combines material and texture + more"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: GState.h,v $
//    $Date: 2001-09-11 22:09:47 $
//    $Revision: 1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////
#ifndef GSTATE_INCLUDED
#define GSTATE_INCLUDED

#include <string>
#include "Material.h"
#include "Texture.h"

namespace kev
{
   class GState
   {
   public:
      GState()
      {
      }
      std::string name;
      Material mat;

      std::string mapName;
      
      /* mutable */Texture texture;
   };
};

#endif
