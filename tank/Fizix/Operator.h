
//////////////////////////////////////////////////////////////////
//
//                         -=     Operator     =-
//
// Definition: "Base class for all DynamicSystem operators"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Operator.h,v $
//    $Date: 2001-10-10 12:39:00 $
//    $Revision: 1.3 $
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
#ifndef PS_OPERATOR_H
#define PS_OPERATOR_H
#include <vector>

#include "Fizix/Operator.h"
#include "Fizix/Memory.h"

namespace ani
{
   template <class __EntityType>
   class DynamicSystem;
   
   template<class __EntityType>
   class Operator : public ani::Memory
   {
   public:
      Operator()
      {
      }
      virtual ~Operator() {}
      virtual void exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta ) = 0;
   };
};

#endif
