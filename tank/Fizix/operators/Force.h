#ifndef FORCES
#define FORCES

#include <Vec3.h>
#include "Fizix/Operator.h"
#include "Fizix/DynamicSystem.h"

namespace ani
{

   // global - acts on all entities in the system
   template<class __EntityType>
   class GlobalOperator : public ani::Operator<__EntityType>
   {
   public:
      GlobalOperator() : mIgnoreList() {}
      virtual ~GlobalOperator() {}
      void ignore( __EntityType* p )
      {
         assert( p->isInSystem() == true && "can't ignore particles not in the system" );
         p->ref();
         mIgnoreList.push_back( p );
         assert( this->isIgnored( p ) == true && "sanity check, it is really in the list now?");
      }
      bool isIgnored( __EntityType* p )
      {
   //      bool found = false;
         std::vector<__EntityType*>::iterator it;
         std::list< std::vector<__EntityType*>::iterator > toKill;
         for (it = mIgnoreList.begin(); it != mIgnoreList.end(); ++it)
         {
            if ((*it)->isInSystem() == false)
            {
               toKill.push_back( it );
            }

            __EntityType* crap = (*it);
            if (crap == p )
            {
               return true;
            }
         }

         if (toKill.size() > 0)
         {
            std::list< std::vector<__EntityType*>::iterator >::iterator kit;
            for (kit = toKill.begin(); kit != toKill.end(); ++kit)
            {
               (*(*kit))->unrefDelete();
               mIgnoreList.erase( (*kit) );
            }
         }
         return false;
      }
   protected:
      std::vector<__EntityType*> mIgnoreList;
   };


   //: Binary force, 
   // a force operator that acts on only two particles in the system.
   template<class __EntityType>
   class BinaryForce : public ani::Operator<__EntityType>
   {
   public:
      BinaryForce(){}
      virtual ~BinaryForce(){}

      //: apply this force function to the particle
      virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta ) = 0;
   };

   //: FORCE
   //  A basic force, will apply it's force to all particles in the system.
   template<class __EntityType>
   class GlobalForce : public GlobalOperator<__EntityType>
   {
   public:
           GlobalForce(){}
           GlobalForce( float x, float y, float z ) : mForce( x, y, z ) {}
           virtual ~GlobalForce(){}
           void setForce( const Vec3<float>& force ) { mForce = force; }

      //: apply this force function to the particle
      virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );

   private:
      Vec3<float> mForce;
   };

   //: FORCE from Viscous Drag
   //  specify a drag coeficient, will reduce the speed of a particle by (k * Vel)
   template<class __EntityType>
   class ViscousDrag : public GlobalForce<__EntityType>
   {
   public:
      ViscousDrag(){}
      ViscousDrag( float coef ) : _dragCoef( coef ) {}
      virtual ~ViscousDrag(){}
      void setDrag( const float& coeficient )
      {
         _dragCoef = coeficient;
      }

      //: apply this force function to the particle
      virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );

   private:
      float _dragCoef;
   };

   //: FORCE by Acceleration
   //  specify an acceleration, will compute the force for each particle to accelerate it that fast
   template<class __EntityType>
   class Acceleration : public GlobalForce<__EntityType>
   {
   public:
      Acceleration() {}
      Acceleration( float x, float y, float z ) : mAcceleration( x, y, z ) 
      {
      }

      virtual ~Acceleration()
      {
      }

      void setAcceleration( const Vec3<float>& acceleration )
      {
         mAcceleration = acceleration;
      }

      //: apply this force function to the particle
      virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );

   private:
      Vec3<float> mAcceleration;
   };

   //: Current (FORCE by some fluid)
   //  FORCE by some fluid (i.e. air, water, goo) accelerates particle until 
   //  it reaches a certain velocity
   template<class __EntityType>
   class Current : public GlobalForce<__EntityType>
   {
   public:
      Current() : mSpeed()
      {
      }

      virtual ~Current()
      {
      }

      void setSpeed( const Vec3<float>& speed )
      {
         mSpeed = speed;
      }

      //: apply this force function to the particle
      virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );

   private:
      Vec3<float> mSpeed;
   };

   // gravity - a specialization of acceleration
   template<class __EntityType>
   class Gravity : public Acceleration<__EntityType>
   {
   public:
      Gravity() : Acceleration<__EntityType>( 0.0f, -9.8195f, 0.0f ) {}
      virtual ~Gravity(){}
   };


   // spring force
   template<class __EntityType>
   class Spring : public BinaryForce<__EntityType>
   {
   public:
      Spring() : mA(NULL), mB(NULL) {}
      virtual ~Spring()
      {
         // give up responsibility for mA and mB if previously set
         if (mA != NULL)
            mA->unrefDelete();
         if (mB != NULL)
            mB->unrefDelete();
      }

      //TODO: refactor this, move it to its superclass.
      void set__EntityTypes( __EntityType* a, __EntityType* b ) 
      {
         // give up responsibility for mA and mB if previously set
         if (mA != NULL)
            mA->unrefDelete();
         if (mB != NULL)
            mB->unrefDelete();

         // take responsibility for a and b
         a->ref(); mA = a;
         b->ref(); mB = b;
      }
      void setSpringConstant( float ks ) { mSpringConstant = ks; }
      void setDampeningConstant( float kd ) { mDampeningConstant = kd; }
      void setRestLength( float length ) { mRestLength = length; }
      virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );
   private:
      float mSpringConstant;
      float mDampeningConstant;
      __EntityType *mA, *mB;
      float mRestLength;
   };

   // TODO: 

   // Steer particles away from a domain of space.      
   // void Avoid(float magnitude, float epsilon, float look_ahead, PDomainEnum dtype, float a0 = 0.0f, float a1
   //           = 0.0f, float a2 = 0.0f, float a3 = 0.0f, float a4 = 0.0f, float a5 = 0.0f, float a6 = 0.0f,
   //          float a7 = 0.0f, float a8 = 0.0f);

   // explosion force

   // gravitate: O(n^2)
   // Accelerate each particle toward each other particle.

   // F = y(m1*m2)/(r^2)

   /*
   The General Gas Law 
   Boyle's and Charles' laws can be conveniently combined into what is known as the General Gas Law, expressed mathematically as
   follows: 

         den1Vol1 = den2Vol2
           ¯¯¯¯       ¯¯¯¯ 
          Temp1       Temp2
   */

   // Leaf Blower:
   // void Jet(float center_x, float center_y, float center_z, float magnitude = 1.0f, float epsilon = P_EPS,
   //           float max_radius = P_MAXFLOAT)
   // Accelerate particles that are near the center of the jet.

   /*
   void Vortex(float center_x, float center_y, float center_z, float axis_x, float axis_y, float axis_z,
              float magnitude = 1.0f, float epsilion = P_EPS, float max_radius = P_MAXFLOAT)
   Swirl particles around a vortex.
   */

   // Flocking












   //: apply this force function to the particle
template< class __EntityType >
void GlobalForce<__EntityType>::exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>::iterator it;
   for ( it = ps.entities().begin(); it != ps.entities().end(); ++it)
   {
      __EntityType& p = *(*it);
      if (this->isIgnored(&p) == false)
      {
         p.applyForce( mForce );
      }
   }
}

//: apply this force function to the particle
template< class __EntityType >
void ViscousDrag<__EntityType>::exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>::iterator it;
   for ( it = ps.entities().begin(); it != ps.entities().end(); ++it)
   {
      __EntityType& p = *(*it);
      if (this->isIgnored( &p ) == false)
      {
         // Calculate the force nesesary to knock of kV velocity

         // get the velocity we need to reduce entities speed
         // eqn: V(new) = V - kV, where k is a coeficient between 0..1
         Vec3<float> antiVelocity = p.linearVelocity() * (-_dragCoef);

         // how much do we have to decelerate it to achieve 'newDesiredVelocity'
         // decelerateAmount = antiVelocity / timeChange;
         // NOTE: timeChange is 1.0, so deceleration is just antiVelocity
         Vec3<float> force = antiVelocity * p.mass();
         p.applyForce( force );
      }
   }
}

//: apply this force function to the particle
template< class __EntityType >
void Acceleration<__EntityType>::exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>::iterator it;
   for ( it = ps.entities().begin(); it != ps.entities().end(); ++it)
   {
      __EntityType& p = *(*it);
      if (this->isIgnored( &p ) == false)
      {
         //                     meters
         // Force = kilograms * ------ = kilograms * acceleration
         //                     sec^2

         // calculate how much force it will take to accelerate the particle
         Vec3<float> force = mAcceleration * p.mass();
         p.applyForce( force );
         //cout<<"Applied force "<<force[0]<<" "<<force[1]<<" "<<force[2]<<"\n"<<flush;
      }
   }
}

//: apply this force function to the particle
template< class __EntityType >
void Current<__EntityType>::exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>::iterator it;
   for ( it = ps.entities().begin(); it != ps.entities().end(); ++it)
   {
      __EntityType& p = *(*it);
      if (this->isIgnored( &p ) == false)
      {
         //                meters   velocity 
         // acceleration = ------ = --------
         //                sec^2      sec
         Vec3<float>& acc = mSpeed;

         //                     meters
         // Force = kilograms * ------ = kilograms * acceleration
         //                     sec^2

         // calculate how much force it will take to accelerate the particle
         Vec3<float> force = acc * p.mass();
         p.applyForce( force );
      }
   }
}

//: apply this force function to the particle
template< class __EntityType >
void Spring<__EntityType>::exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta )
{
   if (mA == NULL || mB == NULL)
      return;

   // does not make sense for this operator to exist if it has nothing 
   // to act upon...
   // note: this could leave the user holding an operator that maybe they thought would stay in the system... oh well, they will have to check the op's isInSystem...
   if (mA->isInSystem() == false || mB->isInSystem() == false)
   {
      ps.remove( this );
      return;
   }

   __EntityType& a = *mA;
   __EntityType& b = *mB;

   // ignoring the particle system...
   Vec3<float> spring_offset = a.position() - b.position();
   Vec3<float> speed_of_approach = a.velocity() - b.velocity();

   // calculate the spring force magnitude.
   float spring_force_mag = mSpringConstant * (spring_offset.length() - mRestLength);
   
   // calculate the damping force magnitude.
   float damping_force_mag = mDampeningConstant * ( speed_of_approach.dot( spring_offset ) / spring_offset.length() );
  
   // what direction the force is in
   Vec3<float> direction = (spring_offset / spring_offset.length());
   
   // calculate the force from the spring and damping forces.
   Vec3<float> force = -( direction * (spring_force_mag + damping_force_mag ));

   a.applyForce( force );
   b.applyForce( -force );
}
} // end of namespace

#endif
