#ifndef GloveApp_COLLIDE_OPERATOR_H
#define GloveApp_COLLIDE_OPERATOR_H
#include <vector>
#include "Fizix/Operator.h"
#include "Fizix/DynamicSystem.h"
#include <extend.h>


//: FORCE by Acceleration
//  specify an acceleration, will compute the force for each particle to accelerate it that fast
template<class __EntityType>
class Acceleration : public ani::Operator<__EntityType>
{
public:
   Acceleration<__EntityType>() : ani::Operator<__EntityType>()
   {
   }
   
   Acceleration<__EntityType>( float x, float y, float z ) : ani::Operator<__EntityType>(), mAcceleration( x, y, z ) 
   {
   }
   
   virtual ~Acceleration<__EntityType>()
   {
   }
   
   void setAcceleration( const Vec3<float>& acceleration )
   {
      mAcceleration = acceleration;
   }

   //: apply this force function to the particle
   virtual void exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
   {
      std::vector<__EntityType*>& entities = ps.entities();
      std::vector<__EntityType*>::iterator it;
      for ( it = entities.begin(); it != entities.end(); ++it)
      {
         __EntityType& p = *(*it);
         //                     meters
         // Force = kilograms * ------ = kilograms * acceleration
         //                     sec^2

         // calculate how much force it will take to accelerate the particle
         Vec3<float> force = mAcceleration * p.mass();
         p.applyForce( force );
      }
   }

private:
   Vec3<float> mAcceleration;
};

// gravity
template<class __EntityType>
class Gravity : public Acceleration<__EntityType>
{
public:
   Gravity<__EntityType>() : Acceleration<__EntityType>( 0.0f, -9.8195f, 0.0f )
   {
   }
   
   virtual ~Gravity<__EntityType>()
   {
   }
};

// some very very cheezy collision with the x/z plane at 0,0,0 (hard coded)
template<class __EntityType>
class CollisionOperator : public ani::Operator<__EntityType>
{
public:
   //: default constructor
   CollisionOperator<__EntityType>() : ani::Operator<__EntityType>(), mFrictionCoef( 0.0f ), mElasticCoef( 1.0f )
   {
   }
   
   //: destructor
   virtual ~CollisionOperator<__EntityType>() 
   {
   }
   
   void setElastic( float e )
   {
      mElasticCoef = e;
   }   
   
   bool collide( const Vec3<float>& position, const Vec3<float>& rayDir, float& dist, Vec3<float>& normal )
   {
      dist = 0;
      const Vec3<float> polygonNormal( 0,1,0 );
      float d = position[1] - 0.0f;
      if ( d <= 0.0f && rayDir.dot( polygonNormal ) >= 0)
      {
         dist = d;
         normal = polygonNormal;
         return true;
      }
      else
         return false;
   }
   
   void computeCollisionForces( const Vec3<float>& polygonNormal, const Vec3<float>& incomingVector, float elastic_coef, float friction_coef, float mass, float timeDelta, Vec3<float>& frictionForce, Vec3<float>& normalForce )
   {
      //: split the reflected vector into normal and tangential 
      //  vectors to the plane

      // project the (reverse of the) incoming vector onto the normal (just distance scalar)
      float dot = (-incomingVector).dot( polygonNormal );

      // project the (reverse of the) incoming vector onto the normal (now the coordinate)
      Vec3<float> normalComponent = polygonNormal * dot;

      // compute perfect reflection using available vectors... 
      // (perfect == don't consider friction/elasticity)
      Vec3<float> reflectionVector = (normalComponent * 2.0f) + incomingVector;

      // compute the tangential component using the available vectors.
      Vec3<float> tangentialComponent = reflectionVector - normalComponent;

      // compute the normal and friction forces
      // 
      // normal: calc the amount of instantaneous force pushing up 
      //         from the ground.  
      // friction: calc the amount of force against the tangential 
      //           direction of motion
      // 
      // NOTE: instantaneous implies we need to calc
      // the amount of force required to halt motion over the 
      // current timestep if the coef is 1 for elastic or 0 for friction
      // (so this is why consider time in the eq)
      normalForce = normalComponent * (1.0f + elastic_coef) * mass / timeDelta;
      frictionForce = -tangentialComponent * friction_coef * mass / timeDelta;

   }   
   virtual void exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
   {
      std::vector<__EntityType*>& entities = ps.entities();
      std::vector<__EntityType*>::iterator it;
      
      for (it = entities.begin(); it != entities.end(); ++it)
      {
         __EntityType& p = *(*it);
         Vec3<float> incomingVector = p.linearVelocity();
         Vec3<float> incomingVectorNormalized = -incomingVector;
         incomingVectorNormalized.normalize();
         
         
         // replace this with a more generic polygon intersection
         Vec3<float> polygonNormal;
         float dist;
         if ( this->collide( p.position(), incomingVectorNormalized, dist, polygonNormal ) )
         {
            Vec3<float> frictionForce, normalForce;
            computeCollisionForces( polygonNormal, incomingVector, mElasticCoef, mFrictionCoef, p.mass(), timeDelta, frictionForce, normalForce );
            
            // apply the two resulting forces.
            p.applyForce( normalForce );
            p.applyForce( frictionForce );
            
            // correct position to prevent sinking...
            p.setPosition( p.position() + polygonNormal * (-dist) );
            
            
            ///////////////////////////////////////////////////////////////////
            // get side vec in the car's world coords
            Matrix4f mat( Matrix4f::identity() );
            kev::quat2mat( p.rotation(), mat );
            Vec3<float> side_vec(1,0,0);
            kev::xformVec( side_vec, mat, side_vec );
    
            computeCollisionForces( side_vec, p.linearVelocity(), 0.1, 0, p.mass(), timeDelta, frictionForce, normalForce );
            p.applyForce( normalForce );
            p.applyForce( frictionForce );
            //std::cout<<normalForce<<" : "<<frictionForce<<"\n"<<std::flush;
            
             
//            std::cout<<"collide force: "<<normalForce + frictionForce<<"\n"<<std::flush;
         }
      }
   }
   
   float mFrictionCoef; // 0.0 == no friction
   float mElasticCoef;  // 1.0 == fully elastic   
};

template<class __EntityType>
class DriveNavigationOperator : public ani::Operator<__EntityType>
{
public:
   //: default constructor
   DriveNavigationOperator<__EntityType>() : ani::Operator<__EntityType>()
   {
   }
   
   //: destructor
   virtual ~DriveNavigationOperator<__EntityType>()
   {
   }
   
   void force( const Vec3<float>& force )
   {
      mForce += force;
      std::cout<<"applying: "<<mForce[0]<<" "<<mForce[1]<<" "<<mForce[2]<<"\n"<<std::flush;
   }   
   
   // |torque| is the amount of torque.
   // torque vector is the axis of rotation 
   // (use right hand rule for direction of twist).
   void torque( const Vec3<float>& torque )
   {
      mTorque = torque;
   }   
   
   void stop()
   {
      mStopping = true;
   }   
   
   virtual void exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
   {
      std::vector<__EntityType*>& entities = ps.entities();
      std::vector<__EntityType*>::iterator it;
      for (it = entities.begin(); it != entities.end(); ++it)
      {
         __EntityType& p = *(*it);
         
         // apply force in direction particle is facing...
         // TODO, maybe this should be moved up to the app level...
         Matrix4f mat( Matrix4f::identity() );
         //vjQuat inv;
         //inv.invert( p.rotation() );
         kev::quat2mat( p.rotation(), mat );
         Vec3<float> rotated_force, rotated_torque(mTorque);
         kev::xformVec( rotated_force, mat, mForce );
         //rotated_torque.xformVec( mat, mTorque );
         
         // apply forces...
         p.applyForce( rotated_force );
         //p.applyTorque( rotated_torque );
         p.setAngularVelocity( rotated_torque );
         
         if (mStopping == true)
         {
            if (p.linearVelocity().length() > 0.0f)
            {
               // calc the amount of force needed to stop immediately 
               // (immediately == in this timestep)
               Vec3<float> force( -p.linearVelocity() * p.mass() / timeDelta );
               p.applyForce( force * timeDelta * 3.0f );

//               Vec3<float> bok = force;
//               std::cout<<"stop force: "<<bok<<"\n"<<std::flush;
            }
         }
      }
      mForce.set( 0,0,0 );
      mTorque.set( 0,0,0 );
      mStopping = false;
   }
   
   Vec3<float> mForce;
   Vec3<float> mTorque; // right hand rule.  |torque| is the amount.
   bool mStopping;
};

#endif
