
//////////////////////////////////////////////////////////////////
//
//               -=     ODE solver using Euler's Method     =-
//
// Definition: "a 1st order ordinary differential equation solver"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: EulerODEsolver.h,v $
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
#ifndef EULER_METHOD
#define EULER_METHOD

#include "Fizix/ODEsolver.h"

namespace ani
{
   //: Euler's algorithm is simple, fast, but unstable at times.
   //  if you need stability, use RungeKutta
   template <class _item>
   class EulerODEsolver : public ODEsolver<_item>
   {
   public:
      EulerODEsolver<_item>() {}
      virtual ~EulerODEsolver<_item>() {}

      // dx = dx/dt*currentState * changeInTime
      // nextState = currentState = currentState + dx
      // before executing this function, 
      //  - you must have zeroed all forces, 
      //  - run each operator on the particle system
      virtual void exec( _item& currentState, float timeDelta )
      {
         //: changeInState = timeDelta * func( currentState, currentTime )
         // f = func(..., ...)
         f.computeDerivative( currentState, timeDelta * 1.0f );
         // changeInState = timeDelta * f
         changeInState.multiplyPhase( f, timeDelta );

         //: nextState = currentState + changeInState
         currentState.addPhase( changeInState );
         currentState.normalize();
      }

      // used to compute the change in currentState
      _item changeInState;

      // temporary used to catch the value of the derivitive function (computeDerivative)
      _item f;
   };
};
#endif
