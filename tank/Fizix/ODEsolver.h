
//////////////////////////////////////////////////////////////////
//
//                   -=     ODE solver base class     =-
//
// Definition: "base class for all ordinary differential equation solvers"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ODEsolver.h,v $
//    $Date: 2001-10-10 12:39:00 $
//    $Revision: 1.2 $
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
#ifndef ODE_SOLVER
#define ODE_SOLVER

#include "Fizix/ODEsolver.h"

namespace ani
{
   // ordinary differential equation solver.
   template <class _item>
   class ODEsolver
   {
   public:
      ODEsolver() {}
      virtual ~ODEsolver() {}

      // give:
      //  currentState = current state of the item
      //  currentTime = current time of the item
      //  timeDelta = current stepsize (t(n) - t(n+1)) == time delta
      // returns:
      //  currentState = x(t0 + h) == the next state of the item after taking this step...
      virtual void exec( _item& currentState, float timeDelta )
      {      
      }
   };
}


#endif
