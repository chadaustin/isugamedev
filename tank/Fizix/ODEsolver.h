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
