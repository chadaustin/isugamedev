
//////////////////////////////////////////////////////////////////
//
//                         -=     SolverFactory     =-
//
// Definition: "a class that creates ODE solvers from a given text string"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: SolverFactory.h,v $
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
