
//////////////////////////////////////////////////////////////////
//
//                         -=     DynamicSystem     =-
//
// Definition: "Container class for particle/body and operators"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: DynamicSystem.h,v $
//    $Date: 2001-10-10 13:21:52 $
//    $Revision: 1.4 $
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
#ifndef SYSTEM_OF_DYNAMIC_ENTITIES
#define SYSTEM_OF_DYNAMIC_ENTITIES

#include <vector>
#include <list>
#include <iostream>

#include <assert.h>
#include "Fizix/Operator.h"
#include "Fizix/Memory.h"  // TODO:: replace with shared_ptr
#include "Fizix/SolverFactory.h"

// ani namespace.
namespace ani
{
   template<class __EntityType>
   class DynamicSystem : public ani::Memory
   {
   public:

      //: constructor
      // create it with new, then ref()
      // i.e. 
      //      ani::DynamicSystem* sys = new ani::DynamicSystem;
      //      sys->ref();
      DynamicSystem<__EntityType>()
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

      //: remove an entity from the system O(1)
      // specify its iterator...
      // this function is useful only to operators (generally).
      //void                          remove( std::vector< __EntityType* >::iterator& it );

      std::vector< __EntityType* >& system() { return mEntities; }
      
      //: remove an operator from the system O(n)
      void                          remove( ani::Operator<__EntityType>* op );


      // clear out all entities, operations, and solver
      void                          clear();

      // clear all entities (result is no entities in the system).
      void                          clearEntities();
      void                          clearOperators();

      // return the last time delta used (or current time delta)
      const float&                  timeDelta() const;

      
      // take one step in the physical model
      virtual void                  step( float timeDelta );

      // specify what solver to use with this system.
      void setSolver( const std::string& solverName = "euler" )
      {
         ODEsolver<__EntityType>* temp = NULL;
         bool result = SolverFactory<__EntityType>::create( solverName, temp );
         if (result)
            mSolver = temp;
      }      
      
   private:
      void zeroForces();
      void execOperations();

   protected:
      std::list<ani::Operator<__EntityType>*>   mOps;
      std::vector<__EntityType*> mEntities;
      ODEsolver<__EntityType>*             mSolver;
      
      // use unrefDelete to delete the memory
      // if you're seeing an error about the destructor, then maybe you're 
      // not creating the DynamicSystem with new ??
      virtual ~DynamicSystem<__EntityType>();
      
   protected:
      float                mTotalTime;
      float                mTimeDelta;
   };  

   template<class __EntityType>
   inline DynamicSystem<__EntityType>::~DynamicSystem<__EntityType>()
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

      std::cout<<"Deleted all memory in PS.\n"<<std::flush;
   }


   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::zeroForces()
   {
      std::vector<__EntityType*>::iterator it;
      for (it = mEntities.begin(); it != mEntities.end(); ++it)
      {
         (*it)->zeroForce();
      }
   }

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::execOperations()
   {
      std::list< ani::Operator<__EntityType>* >::iterator it;
      for (it = mOps.begin(); it != mOps.end(); ++it)
      {
         ani::Operator<__EntityType>& op = *(*it);
         op.exec( *this, mTimeDelta );
      }
   }
   
   // get access to the list of entities so you can render them etc...
   template<class __EntityType>
   inline std::vector<__EntityType*>& ani::DynamicSystem<__EntityType>::entities() { return mEntities; }
   template<class __EntityType>
   inline const std::vector<__EntityType*>& ani::DynamicSystem<__EntityType>::entities() const { return mEntities; }

   template<class __EntityType>
   inline std::list<ani::Operator<__EntityType>*>& ani::DynamicSystem<__EntityType>::operators() { return mOps; }
   template<class __EntityType>
   inline const std::list<ani::Operator<__EntityType>*>& ani::DynamicSystem<__EntityType>::operators() const { return mOps; }

   //: add a function to the system to be executed last
   template<class __EntityType>
   inline void DynamicSystem<__EntityType>::add( ani::Operator<__EntityType>* op )
   {
      assert( op->isInSystem() != true && "ERROR: operator has already been added" );
      op->isInSystem( true );
      op->ref();
      mOps.push_back( op );
   }

   //: add an entity to the system O(1)
   template<class __EntityType>
   inline void DynamicSystem<__EntityType>::add( __EntityType* ent )
   {
      assert( ent->isInSystem() != true && "ERROR: entity has already been added" );
      ent->isInSystem( true ); 
      ent->ref();
      mEntities.push_back( ent );
   }

   //: remove an operator from the system O(n)
   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::remove( ani::Operator<__EntityType>* op )
   {
      assert( op->getRef() == 1 && "ERROR: operator refcount is not 1" );
      assert( op->isInSystem() != false && "ERROR: operator is not part of the system" );
      op->isInSystem( false );
      mOps.remove( op );
      op->unrefDelete();  
   }

   

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::clearEntities()
   {
      std::vector<__EntityType*>::iterator pit;
      for (pit = mEntities.begin(); pit != mEntities.end(); ++pit)
      {
         (*pit)->unrefDelete();
         (*pit) = NULL;
      }
      mEntities.clear();
   }

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::clearOperators()
   {
      std::list<ani::Operator<__EntityType>*>::iterator oit;
      for (oit = mOps.begin(); oit != mOps.end(); ++oit)
      {
         (*oit)->unrefDelete();
         (*oit) = NULL;
      }
      mOps.clear();
   }


   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::clear()
   {
      this->clearEntities();
      this->clearOperators();
   }
   
   //: remove an entity from the system O(1)
   // specify its iterator...
   // this function is useful only to operators (generally).
   /*
   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::remove( std::vector<__EntityType*>::iterator& it )
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
   template<class __EntityType>
   inline const float& ani::DynamicSystem<__EntityType>::timeDelta() const { return mTimeDelta; }

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::step( float timeDelta )
   {
      if (mSolver == NULL)
      {
         this->setSolver( "euler" );
      }
      
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
            mSolver->exec( *entity, mTimeDelta );
         }
      }
   }

}; // end namespace

#endif
