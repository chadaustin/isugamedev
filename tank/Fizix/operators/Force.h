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



} // end of namespace

#endif
