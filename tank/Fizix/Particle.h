
//////////////////////////////////////////////////////////////////
//
//                         -=     Particle     =-
//
// Definition: "particle, just position no rotation, 2nd order derivatives"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Particle.h,v $
//    $Date: 2001-10-10 22:07:50 $
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
#ifndef PARTICLE_INCLUDED_H
#define PARTICLE_INCLUDED_H

#include <Vec3.h>

#include "Fizix/Memory.h"
#include <convert.h>

// Rigid body references:
//  - Thick, very detailed.
//    http://www.cs.cmu.edu/~baraff/sigcourse/
//  - Easy to understand, most is implemented from it.
//    http://www.cs.unc.edu/~ehmann/RigidTutorial/


// ani namespace.
namespace ani
{
   //: Particle, for use in a particle system.
   //  particle is able to do newtonian physics through application of force.
   //  - Dynamic attributes (affected by force) include position, and velocity
   //  - Static attributes (which are not affected by force) include mass, and color.
   //
   // Use Particle objects in conjunction with DynamicSystem, Operator, and ODEsolvers.
   //
   // Notes on "phase space"
   // The motion of a newtonian particle is governed by the familiar f = ma, or, as we will write it here 
   // x'' = a = f/m.  This equation differs from a canonical ODE because it involves a second time derivative, making
   // it a _second_order_ equation.  To handle a second order ODE, we convert it to a first order one by introducing
   // extra variables.  Here we create a variable mVelocity to represent velocity, giving us a pair of coupled first
   // order ODE's: v' = f/m, and x' = v.  This position/velocity product space is called _phase_space_.
   class Particle : public ani::Memory
   {
   public:
      Particle() : ani::Memory(),
               mMass( 1.0f ), mInvMass( 1.0f ), mVolume( 1.0f, 1.0f, 1.0f ),
               mPosition( 0.0f, 0.0f, 0.0f ),
               mLinearMomentum( 0.0f, 0.0f, 0.0f ),
               mForceAccumulator( 0.0f, 0.0f, 0.0f ),
               mDragCoef(1.0f)//, mColor
      {
      }

      Particle( const Particle& p )
      {
         this->copy( p );
      }      

      virtual ~Particle()
      {
      }

   // operations/operators:
   public:

      Particle& operator=( const Particle& p )
      {
         this->copy( p );
         return *this;
      }   

      // this = p
      // copies all attributes.
      inline virtual void copy( const Particle& p )
      {
         mPosition = p.mPosition;           
         mLinearMomentum = p.mLinearMomentum;  
         mForceAccumulator = p.mForceAccumulator;  
         mMass = p.mMass;
         mInvMass = p.mInvMass; 
         mVolume = p.mVolume;         
         mDragCoef = p.mDragCoef;
      }

      //: computeDerivative
      //
      // The behavior of the system is described by an "Ordinary
      // Differential Equation" (ODE) of the form
      // x' = f( x, t )
      // where f is a known function, x is the state of the system
      // and x' is the time derivitive of x.
      //
      // Here, f = computeDerivative, x' = this, and x = currentState;
      // This function computes change due to the force accumulator
      // The x' returned assumes time=1, so for example using Euler's 
      // method to solve the next step, you will have to scale 
      // x' by the amount of time since this func was last called.
      // 
      //
      // this = the time derivitive of "currentState"
      inline virtual void computeDerivative( const Particle& currentState, const float& currentTime )
      {
         // change in position/rotation over time (first order)
            // x' = v = P(t)/M
            mPosition = currentState.linearVelocity();

         // change in momentum over time (second order)
            // P'(t) = F(t)
            mLinearMomentum = currentState.mForceAccumulator;
      }

      virtual void normalize()
      {
      }

      // scale by time.
      // this = a * h
      inline virtual void multiplyPhase( const Particle& a, float h )
      {
         mPosition = a.mPosition * h;
         mLinearMomentum = a.mLinearMomentum * h;
      }

      // scale by time.
      // this *= h
      inline virtual void multiplyPhase( float h )
      {
         mPosition *= h;
         mLinearMomentum *= h;
      }

      // phase space addition operator
      // this = a + b
      inline virtual void addPhase( const Particle& a, const Particle& b )
      {
         mPosition = a.mPosition + b.mPosition;
         mLinearMomentum = a.mLinearMomentum + b.mLinearMomentum;
      }

      // phase space addition operator
      // this += a
      inline virtual void addPhase( const Particle& a ) //
      {
         mPosition += a.mPosition;
         mLinearMomentum += a.mLinearMomentum;
      }

   // state setting/accumulation
   public:   
      void setPosition( const Vec3<float>& position) { mPosition = position; }
      void setVelocity( const Vec3<float>& velocity ) { mLinearMomentum = velocity * mMass; }

      //: Apply a force to the particle
      //  Each call to applyForce adds a force vector and torque to the particle.
      //  call update() to finally apply the accumulated forces which were added with this function.
      //  NOTE: the force applied, should be with respect to 1.0 unit of time.
      void applyForce( const Vec3<float>& force ) 
      { 
         mForceAccumulator += force; 
      }
      
      inline virtual void zeroForce()
      {
         mForceAccumulator.set( 0.0f, 0.0f, 0.0f );
      }

      //: set the mass
      //  units are metric kilograms
      void setMass( const float& kilograms )
      {
         mMass = kilograms;
         
         // precompute the inverse mass
         mInvMass = 1.0f / kilograms;  
      }
      
      void setVolume( Vec3<float> vol )
      {
         mVolume = vol;
      }
      
   // aliases (getters)
   public:
   // "phase space" (see note above)
      inline const Vec3<float>&       position() const { return mPosition; }
      
      //: Calculate v(t)
      inline Vec3<float> linearVelocity() const
      {
         return mLinearMomentum * mInvMass;
      }
      
      inline Vec3<float> linearMomentum() const
      {
         return mLinearMomentum;
      }
       
   // other things needed by ODE to compute changes in the "phase space"
      inline const Vec3<float>& accumulatedForce() const { return mForceAccumulator; }
      inline const float&       mass() const { return mMass; }
      inline const Vec3<float>& volume() const { return mVolume; }

   public:
   //:: "phase space" (see note above)
      // state variables:
      Vec3<float> mPosition;           // meters        - x(t)
      Vec3<float> mLinearMomentum;     // linear momentum P(t)
                                       // mLinearMomentum = mMass * mVelocity

      // derived quantities (aux variables)
      //Vec3<float> mVelocity;         // v(t) (meters/second)
      
   //:: other things needed by ODE to compute changes in the "phase space"

      // accumulation buffers:
      Vec3<float> mForceAccumulator;  // newtons - F(t)
      
      // constant (set) quantities
      float       mMass, mInvMass;    // kilograms
      Vec3<float> mVolume;            // 3D volume (a box)

   // other attribs for the particle.
      float       mDragCoef;          // just a coef from 0 (no drag) to 1 (drag)
   };

}; // ani namespace

#endif
