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
