#ifndef SOLVER_FACTORY
#define SOLVER_FACTORY

#include <string>
#include "Fizix/ODEsolver.h"
#include "Fizix/EulerODEsolver.h"
#include "Fizix/ModifiedEulerODEsolver.h"
#include "Fizix/HeunODEsolver.h"
#include "Fizix/RungeKuttaODEsolver.h"


namespace ani
{

   template <class _item>
   class SolverFactory
   {
   public:
      // request a solver
      static bool create( const std::string& solverName, ODEsolver<_item>* &newSolver )
      {
         if (solverName == "euler")
         {
            newSolver = new EulerODEsolver<_item>;
         }
         else if (solverName == "modified euler")
         {
            newSolver = new ModifiedEulerODEsolver<_item>;
         }
         else if (solverName == "heun")
         {
            newSolver = new HeunODEsolver<_item>;
         }
         else if (solverName == "runge kutta")
         {
            newSolver = new RungeKuttaODEsolver<_item>;
         }
         else 
         {
            // default, most simple, fast
            newSolver = new EulerODEsolver<_item>;
         }      
         return true;
      } 
   };

}

#endif
