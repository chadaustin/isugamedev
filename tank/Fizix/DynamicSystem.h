#ifndef SYSTEM_OF_DYNAMIC_ENTITIES
#define SYSTEM_OF_DYNAMIC_ENTITIES

#include <list>
#include <vector>
#include <assert.h>
#include <iostream.h>
#include "Fizix/Operator.h"
#include "Fizix/Memory.h"  // TODO:: replace with shared_ptr


// ani namespace.
namespace ani
{
   template<class __EntityType, class __ODEsolverType>
   class DynamicSystem : public ani::Memory
   {
   public:

      //: constructor
      // create it with new, then ref()
      // i.e. 
      //      ani::DynamicSystem* sys = new ani::DynamicSystem;
      //      sys->ref();
      DynamicSystem<__EntityType, __ODEsolverType>()
      {
      }

      // get access to the list of entities so you can render them etc...
      std::vector<__EntityType*>&         entities();
      const std::vector<__EntityType*>&   entities() const;

      std::list<ani::Operator<__EntityType>*>&       operators();
      const std::list<ani::Operator<__EntityType>*>& operators() const;

      //: add a function to the system to be executed last
      void                          add( ani::Operator<__EntityType>* op );

      //: add an entity to the system O(1)
      void                          add( __EntityType* ent );

      //: remove an operator from the system O(n)
      void                          remove( ani::Operator<__EntityType>* op );

      //: remove an entity from the system O(1)
      // specify its iterator...
      // this function is useful only to operators (generally).
      //void                          remove( std::vector<__EntityType*>::iterator& it );

      // clear out all entities, operations, and solver
      void                          clear();

      // clear all entities (result is no entities in the system).
      void                          clearEntities();
      void                          clearOperators();

      // return the last time delta used (or current time delta)
      const float&                  timeDelta() const;

      
      // take one step in the physical model
      virtual void                  step( float timeDelta );

      
   private:
      void zeroForces();
      void execOperations();

   protected:
      std::list<ani::Operator<__EntityType>*>   mOps;
      std::vector<__EntityType*> mEntities;
      __ODEsolverType             mSolver;
      
      // use unrefDelete to delete the memory
      // if you're seeing an error about the destructor, then maybe you're 
      // not creating the DynamicSystem with new ??
      virtual ~DynamicSystem<__EntityType, __ODEsolverType>();
      
   protected:
      float                mTotalTime;
      float                mTimeDelta;
   };  

   template<class __EntityType, class __ODEsolverType>
   inline DynamicSystem<__EntityType, __ODEsolverType>::~DynamicSystem<__EntityType, __ODEsolverType>()
   {
      std::vector<__EntityType*>::iterator pit;
      for (pit = mEntities.begin(); pit != mEntities.end(); ++pit)
      {
         (*pit)->unrefDelete();
         (*pit) = NULL;
      }
      mEntities.clear();

      std::list<ani::Operator<__EntityType>*>::iterator oit;
      for (oit = mOps.begin(); oit != mOps.end(); ++oit)
      {
         (*oit)->unrefDelete();
         (*oit) = NULL;
      }
      mOps.clear();

      cout<<"Deleted all memory in PS.\n"<<flush;
   }


   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::zeroForces()
   {
      std::vector<__EntityType*>::iterator it;
      for (it = mEntities.begin(); it != mEntities.end(); ++it)
      {
         (*it)->zeroForce();
      }
   }

   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::execOperations()
   {
      std::list< ani::Operator<__EntityType>* >::iterator it;
      for (it = mOps.begin(); it != mOps.end(); ++it)
      {
         ani::Operator<__EntityType>& op = *(*it);
         op.exec( this->entities(), mTimeDelta );
      }
   }
   
   // get access to the list of entities so you can render them etc...
   template<class __EntityType, class __ODEsolverType>
   inline std::vector<__EntityType*>& ani::DynamicSystem<__EntityType, __ODEsolverType>::entities() { return mEntities; }
   template<class __EntityType, class __ODEsolverType>
   inline const std::vector<__EntityType*>& ani::DynamicSystem<__EntityType, __ODEsolverType>::entities() const { return mEntities; }

   template<class __EntityType, class __ODEsolverType>
   inline std::list<ani::Operator<__EntityType>*>& ani::DynamicSystem<__EntityType, __ODEsolverType>::operators() { return mOps; }
   template<class __EntityType, class __ODEsolverType>
   inline const std::list<ani::Operator<__EntityType>*>& ani::DynamicSystem<__EntityType, __ODEsolverType>::operators() const { return mOps; }

   //: add a function to the system to be executed last
   template<class __EntityType, class __ODEsolverType>
   inline void DynamicSystem<__EntityType, __ODEsolverType>::add( ani::Operator<__EntityType>* op )
   {
      assert( op->isInSystem() != true && "ERROR: operator has already been added" );
      op->isInSystem( true );
      op->ref();
      mOps.push_back( op );
   }

   //: add an entity to the system O(1)
   template<class __EntityType, class __ODEsolverType>
   inline void DynamicSystem<__EntityType, __ODEsolverType>::add( __EntityType* ent )
   {
      assert( ent->isInSystem() != true && "ERROR: entity has already been added" );
      ent->isInSystem( true ); 
      ent->ref();
      mEntities.push_back( ent );
   }

   //: remove an operator from the system O(n)
   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::remove( ani::Operator<__EntityType>* op )
   {
      assert( op->getRef() == 1 && "ERROR: operator refcount is not 1" );
      assert( op->isInSystem() != false && "ERROR: operator is not part of the system" );
      op->isInSystem( false );
      mOps.remove( op );
      op->unrefDelete();  
   }

   

   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::clearEntities()
   {
      std::vector<__EntityType*>::iterator pit;
      for (pit = mEntities.begin(); pit != mEntities.end(); ++pit)
      {
         (*pit)->unrefDelete();
         (*pit) = NULL;
      }
      mEntities.clear();
   }

   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::clearOperators()
   {
      std::list<ani::Operator<__EntityType>*>::iterator oit;
      for (oit = mOps.begin(); oit != mOps.end(); ++oit)
      {
         (*oit)->unrefDelete();
         (*oit) = NULL;
      }
      mOps.clear();
   }


   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::clear()
   {
      this->clearEntities();
      this->clearOperators();
   }
   
   //: remove an entity from the system O(1)
   // specify its iterator...
   // this function is useful only to operators (generally).
   /*
   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::remove( std::vector<__EntityType*>::iterator& it )
   {
      __EntityType* p = (*it);
      assert( p->getRef() == 1 && "ERROR: entity refcount is not 1" );
      assert( p->isInSystem() != false && "ERROR: entity is not part of the system" );
      p->isInSystem( false );
      mEntities.erase( it );
      p->unrefDelete();
   }
   */
      
   // return the last time delta used (or current time delta)
   template<class __EntityType, class __ODEsolverType>
   inline const float& ani::DynamicSystem<__EntityType, __ODEsolverType>::timeDelta() const { return mTimeDelta; }

   template<class __EntityType, class __ODEsolverType>
   inline void ani::DynamicSystem<__EntityType, __ODEsolverType>::step( float timeDelta )
   {
      // make sure bogus values don't get processed...
      // mostly im afraid of numbers in the 40e+8 range
      // but really it shouldn't go lower than 100
      if (timeDelta < 100.0f && timeDelta > 0.0f)
      {
         mTotalTime += timeDelta;
         mTimeDelta = timeDelta;

         // set the forces in mEntities
         this->zeroForces();
         this->execOperations();

         // solve for the next state the entities are at
         std::vector<__EntityType*>::iterator it;
         for (it = mEntities.begin(); it != mEntities.end(); ++it)
         {
            __EntityType* entity = (*it);
            mSolver.exec( *entity, mTimeDelta );
         }
      }
   }

}; // end namespace

#endif
