
//////////////////////////////////////////////////////////////////////////////
//
//                         -= glRenderLight =-
//
// Description: "decoupled Light renderer for OGL"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: glRenderLight.h,v $
//    $Date: 2001-09-30 21:54:00 $
//    $Revision: 1.7 $
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
#ifndef GLRENDERLIGHT_H_INCLUDED
#define GLRENDERLIGHT_H_INCLUDED

#include "Light.h"

namespace kev
{
   
   void glRender( const Light& light );
};


#endif // ! GLRENDERLIGHT_H_INCLUDED
