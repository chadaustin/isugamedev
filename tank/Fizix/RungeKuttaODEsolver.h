#ifndef RUNGEKUTTA_METHOD
#define RUNGEKUTTA_METHOD

namespace ani
{
   //: the fourth-order Runge-Kutta method is generally considered to provide an 
   // excellent balance of power, precision [O(h^5)], and simplicity to program. 
   // Here there are four gradient or ``k'' terms which provide a better approximation 
   // to the behavior of f(t,y) near the midpoint...
   template <class _item>
   class RungeKuttaODEsolver
   {
   public:
      RungeKuttaODEsolver() {}
      ~RungeKuttaODEsolver() {}

      //: the fourth-order Runge-Kutta method 
      //
      // give:
      //  currentState = current state of the item
      //  currentTime = current time of the item
      //  timeDelta = current stepsize (t(n) - t(n+1)) == time delta
      // returns:
      //  currentState = x(t0 + h) == the next state of the item after taking this step...
      inline void exec( _item& currentState, float timeDelta )
      {
         static const float oneOverSix = (1.0f/6.0f);

         // compute next state.
            
            // any particle that is put into f() needs to have its mass and force accums set
            // to equal the current _item, since all the operations only act on the phase space
            // (pos, vel), this is needed:
            _item temp( currentState );


            // k1 = h * func( x0, t0 );
            //     f = func(..., ...)
            f.computeDerivative( currentState, timeDelta * 0.0f );
            //     k1 = h * f
            k1.multiplyPhase( f, timeDelta );


            //: k2 = h * func( x0 + k1*0.5f, t0 + h*0.5f );
            //     f = func(..., ...)
            temp.multiplyPhase( k1, 0.5f );
            temp.addPhase( currentState, temp );
            f.computeDerivative( temp, timeDelta * 0.5f ); 
            //     k2 = h * f
            k2.multiplyPhase( f, timeDelta );

            //: k3 = h * func( x0 + k2*0.5f, t0 + h*0.5f );
            //     f = func(..., ...)
            temp.multiplyPhase( k2, 0.5f );
            temp.addPhase( currentState, temp );
            f.computeDerivative( temp, timeDelta * 0.5f ); 
            //     k3 = h * f
            k3.multiplyPhase( f, timeDelta );

            //: k4 = h * func( x0 + k3, t0 + h );
            //     f = func(..., ...)
            temp.addPhase( currentState, k3 );
            f.computeDerivative( temp, timeDelta * 1.0f );
            //     k4 = h * f
            k4.multiplyPhase( f, timeDelta );

            // xt0h = x0  +  1/6 * k1  +  1/3 * k2  +  1/3 * k3  +  1/6 * k4;
            //currentState = currentState + (oneOverSix * (k1 + 2.0f * (k2 + k3) + k4));
            changeInState.addPhase( k2, k3 );
            changeInState.multiplyPhase( 2.0f );
            changeInState.addPhase( k1 );
            changeInState.addPhase( k4 );
            changeInState.multiplyPhase( oneOverSix );

            currentState.addPhase( currentState, changeInState );
            currentState.normalize();
      }

      // the four gradient or ``k'' terms
      _item k1, k2, k3, k4;
      _item changeInState, f;
   };
}; // end namespace

#endif
