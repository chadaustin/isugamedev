
//////////////////////////////////////////////////////////////////
//
//               -=     ODE solver using Heun's Method     =-
//
// Definition: "a 2nd order ordinary differential equation solver"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: HeunODEsolver.h,v $
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
#ifndef SECONDORDER_RUNGEKUTTA_METHOD
#define SECONDORDER_RUNGEKUTTA_METHOD

#include "Fizix/ODEsolver.h"

namespace ani
{

   //: the second-order Runge-Kutta method 
   template <class _item>
   class HeunODEsolver : public ODEsolver<_item>
   {
   public:
      HeunODEsolver() {}
      virtual ~HeunODEsolver() {}

      //: the second-order Runge-Kutta method 
      //
      // give:
      //  currentState = current state of the item
      //  currentTime = current time of the item
      //  timeDelta = current stepsize (t(n) - t(n+1)) == time delta
      // returns:
      //  currentState = x(t0 + h) == the next state of the item after taking this step...
      virtual void exec( _item& currentState, float timeDelta )
      {      
         // compute next state.
         
         // any particle that is put into f() needs to have its mass and force accums set
         // to equal the current _item, since all the operations only act on the phase space
         // (pos, vel), this is needed.
         temp.copy( currentState );

         // k1 = h * func( x0, t0 );
         //     f = func(..., ...)
         f.computeDerivative( currentState, timeDelta * 0.0f );
         //     k1 = h * f
         k1.multiplyPhase( f, timeDelta );

         //: k2 = h * func( x0 + k1, t0 + h );
         //     f = func(..., ...)
         temp.addPhase( currentState, k1 );
         f.computeDerivative( temp, timeDelta * 1.0f );
         //     k4 = h * f
         k2.multiplyPhase( f, timeDelta );

         // xt0h = x0  +  1/2 * (k1  +  k2);
         //currentState = currentState + 1/2 * (k1 + k2);
         changeInState.addPhase( k1, k2 );
         changeInState.multiplyPhase( 0.5f );

         currentState.addPhase( changeInState );
         currentState.normalize();
      }

      // create the two gradient or ``k'' terms
      _item k1, k2;
      _item changeInState, f, temp;
   };
};

#endif
