
//////////////////////////////////////////////////////////////////
//
//                         -=     Rigid Body     =-
//
// Definition: "rigid body, has position and rotation, 2nd order derivative"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Body.h,v $
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
#ifndef BODY
#define BODY

#include <Matrix4f.h>
#include <Vec3.h>
#include <Quat.h>

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
   // So we can easilly get R = ( a x b(col0)  a x b(col1)  a x b(col2) )
   // by computing R = (a*) * b
   //
   // Given a vector a, lets define a* to be the matrix
   // (a*) * b == a x b   (where a and b are vectors, a* is matrix)
   // What's impressive is this:
   // (a*) * b == R       (where b is now a matrix, the result is a matrix who's columns are a x b(i))
   inline static void starOperator( const Vec3<float>& a, Matrix4f& aStar )
   {
      aStar.makeIdent();
      aStar(0,0) = 0.0f;
      aStar(0,1) = a[2];
      aStar(0,2) = -a[1];

      aStar(1,0) = -a[2];
      aStar(1,1) = 0.0f;
      aStar(1,2) = a[0];

      aStar(2,0) = a[1];
      aStar(2,1) = -a[0];
      aStar(2,2) = 0.0f;
   }     

   //: Body, for use in a particle system.
   //  particle is able to do newtonian physics through application of force.
   //  - Dynamic attributes (affected by force) include position, and velocity
   //  - Static attributes (which are not affected by force) include mass, and color.
   //
   // Use Body objects in conjunction with DynamicSystem, Operator, and ODEsolvers.
   //
   // Notes on "phase space"
   // The motion of a newtonian particle is governed by the familiar f = ma, or, as we will write it here 
   // x'' = a = f/m.  This equation differs from a canonical ODE because it involves a second time derivative, making
   // it a _second_order_ equation.  To handle a second order ODE, we convert it to a first order one by introducing
   // extra variables.  Here we create a variable mVelocity to represent velocity, giving us a pair of coupled first
   // order ODE's: v' = f/m, and x' = v.  This position/velocity product space is called _phase_space_.
   class Body : public ani::Memory
   {
   public:
      Body() : ani::Memory(),
               mMass( 1.0f ), mInvMass( 1.0f ), mVolume( 1.0f, 1.0f, 1.0f ),
               mBodySpaceInertiaTensor(), mBodySpaceInertiaTensorInv(), 

               mPosition( 0.0f, 0.0f, 0.0f ),
               mRotation(),

               mLinearMomentum( 0.0f, 0.0f, 0.0f ),
               mAngularMomentum( 0.0f, 0.0f, 0.0f ),

               mForceAccumulator( 0.0f, 0.0f, 0.0f ),
               mTorqueAccumulator( 0.0f, 0.0f, 0.0f ),

               mDragCoef(1.0f)//, mColor
      {
      }

      Body( const Body& p )
      {
         this->copy( p );
      }      

      virtual ~Body()
      {
      }

   // operations/operators:
   public:

      Body& operator=( const Body& p )
      {
         this->copy( p );
         return *this;
      }   

      // this = p
      // copies all attributes.
      inline void copy( const Body& p )
      {
         mPosition = p.mPosition;           
         mRotation = p.mRotation;          
         mLinearMomentum = p.mLinearMomentum;  
         mAngularMomentum = p.mAngularMomentum;   
         //mWorldSpaceInertiaTensorInv = p.mWorldSpaceInertiaTensorInv; 
         //mVelocity = p.mVelocity;       
         //mAngularVelocity = p.mAngularVelocity;   
         mForceAccumulator = p.mForceAccumulator;  
         mTorqueAccumulator = p.mTorqueAccumulator; 
         mMass = p.mMass;
         mInvMass = p.mInvMass; 
         mVolume = p.mVolume;         
         mBodySpaceInertiaTensor = p.mBodySpaceInertiaTensor;
         mBodySpaceInertiaTensorInv = p.mBodySpaceInertiaTensorInv; 
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
      inline void computeDerivative( const Body& currentState, const float& currentTime )
      {
         // change in position/rotation over time (first order)
            // x' = v = P(t)/M
            mPosition = currentState.linearVelocity();

            // R'(t) = w(t)*' R(t)   (matrix version)
            // q'(t) = 1/2 w(t) q(t) (quaternion version)
            //mRotation = 0.5f * currentState.angularVelocity() * currentState.mRotation;
            Quat<float> ang_vel_quat; 
            ang_vel_quat.makePure( currentState.angularVelocity() * 0.5f );
            mRotation.mult( ang_vel_quat, currentState.mRotation );

         // change in momentum over time (second order)
            // P'(t) = F(t)
            mLinearMomentum = currentState.mForceAccumulator;

            // L'(t) = T(t)
            mAngularMomentum = currentState.mTorqueAccumulator;
      }

      void normalize()
      {
         mRotation.normalize();
      }

      // scale by time.
      // this = a * h
      inline void multiplyPhase( const Body& a, float h )
      {
         mPosition = a.mPosition * h;
         mRotation.mult( a.mRotation, h );
         mLinearMomentum = a.mLinearMomentum * h;
         mAngularMomentum = a.mAngularMomentum * h;
      }

      // scale by time.
      // this *= h
      inline void multiplyPhase( float h )
      {
         mPosition *= h;
         mRotation.mult( mRotation, h );
         mLinearMomentum *= h;
         mAngularMomentum *= h;
      }

      // phase space addition operator
      // this = a + b
      inline void addPhase( const Body& a, const Body& b )
      {
         mPosition = a.mPosition + b.mPosition;
         mRotation.add( a.mRotation, b.mRotation );
         mLinearMomentum = a.mLinearMomentum + b.mLinearMomentum;
         mAngularMomentum = a.mAngularMomentum + b.mAngularMomentum;
      }

      // phase space addition operator
      // this += a
      inline void addPhase( const Body& a ) //
      {
         mPosition += a.mPosition;
         mRotation.add( a.mRotation, mRotation );
         mLinearMomentum += a.mLinearMomentum;
         mAngularMomentum += a.mAngularMomentum;
      }

   // state setting/accumulation
   public:   
      void setPosition( const Vec3<float>& position) { mPosition = position; }
      void setVelocity( const Vec3<float>& velocity ) { mLinearMomentum = velocity * mMass; }
      void setRotation( const Quat<float>& rot ) { mRotation = rot; }

      // set angular momentum with the given angular velocity
      // calculate L(t), if w(t) is known...
      // PRE: mass and vol should be set first.
      void setAngularVelocity( Vec3<float>& angularVel )
      {
         mAngularMomentum = mBodySpaceInertiaTensor * angularVel;
      }

      //: Apply a force to the particle
      //  Each call to applyForce adds a force vector and torque to the particle.
      //  call update() to finally apply the accumulated forces which were added with this function.
      //  NOTE: the force applied, should be with respect to 1.0 unit of time.
      void applyForce( const Vec3<float>& force ) 
      { 
         mForceAccumulator += force; 
      }
      
      // apply a force to a position on the body.
      // this results in a rotation (torque)
      void applyTorque( const Vec3<float>& force, const Vec3<float>& location, const Vec3<float>& center )
      {
         mTorqueAccumulator += (location - center).cross( force );
      }

      //: Apply a torque to the particle
      //   torque  is the axis of spin
      //  |torque| is the magnitude (i.e. don't normalize this vec!)
      void applyTorque( const Vec3<float>& torque )
      {
         mTorqueAccumulator += torque;
      }

      inline void zeroForce()
      {
         mForceAccumulator.set( 0.0f, 0.0f, 0.0f );
         mTorqueAccumulator.set( 0.0f, 0.0f, 0.0f );
      }

      //: set the mass
      //  units are metric kilograms
      void setMass( const float& kilograms )
      {
         mMass = kilograms;
         
         // precompute the inverse mass
         mInvMass = 1.0f / kilograms;  
         
         // precompute the body-space inertia tensor
         this->precalcBodyInertiaTensorForBlock();
      }
      
      void setVolume( Vec3<float> vol )
      {
         mVolume = vol;
         
         // precompute the body inertia tensor
         this->precalcBodyInertiaTensorForBlock();
      }
      
   // aliases (getters)
   public:
   // "phase space" (see note above)
      inline const Vec3<float>&       position() const { return mPosition; }
      inline const Quat<float>&       rotation() const { return mRotation; }
      
      //: Calculate v(t)
      inline Vec3<float> linearVelocity() const
      {
         return mLinearMomentum * mInvMass;
      }
      

      //: Calculate w(t) using given inertia tensor
      // w(t) = I^-1(t) L(t)
      inline Vec3<float> angularVelocity( const Matrix4f& ws_tensor_inv ) const
      {
         Vec3<float> temp;
         temp = ws_tensor_inv * mAngularMomentum;
         return temp;
      }
      
      //: Calculate w(t), calcs the inertia tensor for you.
      //  w(t) = I^-1(t) L(t)
      inline Vec3<float> angularVelocity() const
      {
         Matrix4f world_space_inertia_tensor_inv;
         calcWorldSpaceInertiaTensor( world_space_inertia_tensor_inv );
         
         return this->angularVelocity( world_space_inertia_tensor_inv );
      }
      
      inline Vec3<float> linearMomentum() const
      {
         return mLinearMomentum;
      }
      
      inline Vec3<float> angularMomentum() const
      {
         return mAngularMomentum;
      }
       
   // other things needed by ODE to compute changes in the "phase space"
      inline const Vec3<float>&       accumulatedForce() const { return mForceAccumulator; }
      inline const Vec3<float>&       accumulatedTorque() const { return mTorqueAccumulator; }
      inline const float&        mass() const { return mMass; }
      inline const Vec3<float>&       volume() const { return mVolume; }

   public:
   //:: "phase space" (see note above)
      // state variables:
      Vec3<float> mPosition;           // meters        - x(t)
      Quat<float> mRotation;           // radians       - q(t) or R(t)
      Vec3<float> mLinearMomentum;     // linear momentum P(t)
                                  // mLinearMomentum = mMass * mVelocity
      Vec3<float> mAngularMomentum;    // angular momemtum - L(t)
                                  // |L| is how fast, L is the axis
                                  // L(t) = Ibody(t) * w(t)
      
      // derived quantities (aux variables)
      //Vec3<float> mVelocity;         // v(t) (meters/second)
      //Matrix4f mRotationM;      // R(t) (rotation matrix) 
      
      // The body may also be spinning. It spins about an axis through the 
      // center of mass. This axis is represented by a vector. The magnitude 
      // of the vector defines how fast the body is spinning and the direction 
      // of the vector defines the axis about which the body rotates. This it 
      // called the angular velocity w(t).
      //Vec3<float> mAngularVelocity;              // w(t) or "omega"
      //Matrix4f mWorldSpaceInertiaTensorInv; // tensor in world space coords.
      
   //:: other things needed by ODE to compute changes in the "phase space"

      // accumulation buffers:
      Vec3<float>      mForceAccumulator;  // newtons - F(t)
      Vec3<float>      mTorqueAccumulator; // torque - T(t)

      // constant (set) quantities
      float       mMass, mInvMass;    // kilograms
      Vec3<float>      mVolume;            // 3D volume (a box)

      // The inertia tensor is a 3x3 matrix describing how the shape and mass 
      // distribution of the body is affected by the angular velocity. It can 
      // be thought of as a scaling factor between angular momentum and 
      // angular velocity. This matrix is computed in body space and then 
      // transformed as needed to world space. It is given as the matrix:
      // Ibody, and Ibodyinv:
      Matrix4f mBodySpaceInertiaTensor, mBodySpaceInertiaTensorInv; // Ibody(t) (inertia tensor)

   // other attribs for the particle.
      float       mDragCoef;          // just a coef from 0 (no drag) to 1 (drag)
   
   // recalc funcs
   private:
      //: Precompute the inertia tensor in local (body) coordinates
      //
      // By using body space coordinates we can cheaply compute the inertia 
      // tensor for any orientation R(t) in terms of a precomputed integral 
      // in body space coordinates.  This is typically computed before the 
      // simulation begins and should be regarded as one of the input params.
      //
      // here we do a quick calc of Ibody(t) if the object is cube shaped
      void precalcBodyInertiaTensorForBlock()
      {
         mBodySpaceInertiaTensor.makeIdent();
         mBodySpaceInertiaTensor(0,0) = mMass * (mVolume[1]*mVolume[1] + mVolume[2]*mVolume[2]);
         mBodySpaceInertiaTensor(1,1) = mMass * (mVolume[0]*mVolume[0] + mVolume[2]*mVolume[2]);
         mBodySpaceInertiaTensor(2,2) = mMass * (mVolume[0]*mVolume[0] + mVolume[1]*mVolume[1]);
         
         float scalar = 12.0f;
         mBodySpaceInertiaTensor(0,0) /= scalar;
         mBodySpaceInertiaTensor(1,1) /= scalar;
         mBodySpaceInertiaTensor(2,2) /= scalar;

         mBodySpaceInertiaTensorInv.invert( mBodySpaceInertiaTensor );
      }
      
      //: Precompute the inertia tensor in local (body) coordinates
      //
      // By using body space coordinates we can cheaply compute the inertia 
      // tensor for any orientation R(t) in terms of a precomputed integral 
      // in body space coordinates.  This is typically computed before the 
      // simulation begins and should be regarded as one of the input params.
      //
      // A simple way to compute the tensor matix is to create a bounding box 
      // around the polyhedron and sample inside this box. We accumulate 
      // the matrix as the sum of all the sample points scaled by the total 
      // mass and the number of points sampled. When a sample point falls 
      // inside the body, we add to the already accumulated matrix.  When a 
      // sample falls outside of the body, we do nothing. Some code to do 
      // this is given here: 
      /*
      void calcBodyInertiaTensorGeneral()
      {
         Matrix4f mat;
         mBodySpaceInertiaTensor = mat;
         float low = -mVolume[0];
         float high = mVolume[0];
         float hits = 0.0f;
         for (int x = low; x < high; ++x)
         for (int y = low; y < high; ++y)
         for (int z = low; z < high; ++z)
         {
            if (x,y,z sample point falls within the body)
            {
               mat(0,0) = y * y + z * z;
               mat(0,1) = -(x * y );
               mat(0,2) = -(x * y );

               mat(1,0) = -(x * y );
               mat(1,1) = x * x + z * z;
               mat(1,2) = -(y * z );

               mat(2,0) = -(x * z );
               mat(2,1) = -(y * z );
               mat(2,2) = x * x + y * y;

               mBodySpaceInertiaTensor = mBodySpaceInertiaTensor + mat;
               ++hits;
            }
         }
         mBodySpaceInertiaTensor = (mMass/hits) * mBodySpaceInertiaTensor;
         mBodySpaceInertiaTensorInv.invert( mBodySpaceInertiaTensor );
      }
      */

      //: Calculate I^-1(t)
      //  I^-1(t) = R(t)  Ibody^-1(t)  R(t)^T
      void calcWorldSpaceInertiaTensor( Matrix4f& worldSpaceInertiaTensorInv ) const
      {
         Matrix4f r, rT;
         
         // The orientation matrix R(t), which is needed to compute I^-1(t), 
         // will be computed as an auxiliary variable from q(t)
         kev::quat2mat( mRotation, r );
         
         // transpose of R(t)
         rT.transpose( r );
         
         // compute I^-1(t) from current rotation and the body-space 
         // inertia tensor
         worldSpaceInertiaTensorInv = r * (mBodySpaceInertiaTensorInv * rT);
      }
   };

}; // ani namespace

#endif
