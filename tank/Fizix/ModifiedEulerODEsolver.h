
//////////////////////////////////////////////////////////////////
//
//           -=     ODE solver using a Modified Euler's Method    =-
//
// Definition: "a 1st order ordinary differential equation solver"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ModifiedEulerODEsolver.h,v $
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
#ifndef MODIFIED_EULER_METHOD
#define MODIFIED_EULER_METHOD

#include "Fizix/ODEsolver.h"

namespace ani
{
   //: simple, fast, unstable at times.
   template <class _item>
   class ModifiedEulerODEsolver : public ODEsolver<_item>
   {
   public:
      ModifiedEulerODEsolver() {}
      virtual ~ModifiedEulerODEsolver() {}

      // dx = dx/dt*currentState * changeInTime
      // nextState = currentState = currentState + dx
      // before executing this function, 
      //  - you must have zeroed all forces, 
      //  - run each operator on the particle system
      virtual void exec( _item& currentState, float timeDelta )
      {
         // compute next state.
         
         // any particle that is put into f() needs to have its mass and force accums set
         // to equal the current _item, since all the operations only act on the phase space
         // (pos, vel), this is needed:
         _item temp( currentState );

         // k1 = h * func( x0, t0 );
         //     f = func(..., ...)
         f.computeDerivative( currentState, 0.0f * timeDelta );
         //     k1 = h * f
         k1.multiplyPhase( f, timeDelta );

         //: k2 = h * func( x0 + 1/2*k1, t0 + 1/2 * h );
         //     f = func(..., ...)
         temp.multiplyPhase( k1, 0.5f );
         temp.addPhase( temp, currentState );
         f.computeDerivative( temp, 0.5f * timeDelta );
         //     k2 = h * f
         k2.multiplyPhase( f, timeDelta );

         // xt0h = x0  +  k2;
         currentState.addPhase( k2 ); 
         currentState.normalize();
      }

      _item k1, k2;

      // temporary used to catch the value of the derivitive function (computeDerivative)
      _item f;
   };
};
#endif
