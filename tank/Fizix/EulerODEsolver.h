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
