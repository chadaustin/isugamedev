#ifndef SECONDORDER_RUNGEKUTTA_METHOD
#define SECONDORDER_RUNGEKUTTA_METHOD

namespace ani
{

   //: the second-order Runge-Kutta method 
   template <class _item>
   class HeunODEsolver
   {
   public:
      HeunODEsolver() {}
      ~HeunODEsolver() {}

      //: the second-order Runge-Kutta method 
      //
      // give:
      //  currentState = current state of the item
      //  currentTime = current time of the item
      //  timeDelta = current stepsize (t(n) - t(n+1)) == time delta
      // returns:
      //  currentState = x(t0 + h) == the next state of the item after taking this step...
      inline void exec( _item& currentState, float timeDelta )
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
