
//////////////////////////////////////////////////////////////////
//
//                         -=     DynamicSystem     =-
//
// Definition: "Container class for particle/body and operators"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: DynamicSystem.h,v $
//    $Date: 2001-10-17 03:42:50 $
//    $Revision: 1.6 $
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
#include <boost/smart_ptr.hpp>
#include "Fizix/Operator.h"
#include "Fizix/Memory.h"  // TODO:: replace with shared_ptr
#include "Fizix/SolverFactory.h"

// ani namespace.
namespace ani
{
   template<class __EntityType>
   class DynamicSystem : public __EntityType
   {
   public:
      // Need a shared pointer for the entity and operator types
      typedef boost::shared_ptr<__EntityType> EntityTypePtr;
      typedef boost::shared_ptr< ani::Operator<__EntityType> > OperatorPtr;

   public:

      //: constructor
      DynamicSystem<__EntityType>()
      {
      }

      // if you're seeing an error about the destructor, then maybe you're 
      // not creating the DynamicSystem with new ??
      virtual ~DynamicSystem<__EntityType>()
      {
      }
 
      // get access to the list of entities so you can render them etc...
      std::vector<EntityTypePtr>&         entities();
      const std::vector<EntityTypePtr>&   entities() const;

      std::list<OperatorPtr>&       operators();
      const std::list<OperatorPtr>& operators() const;

      //: add a function to the system to be executed last
      void                          add( OperatorPtr op );

      //: add an entity to the system O(1)
      void                          add( EntityTypePtr ent );

      //: remove an entity from the system O(1)
      // specify its iterator...
      // this function is useful only to operators (generally).
      //void                          remove( std::vector< __EntityType* >::iterator& it );

      std::vector< EntityTypePtr >& system() { return mEntities; }
      
      //: remove an operator from the system O(n)
      void                          remove( OperatorPtr op );


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
      std::list<OperatorPtr>        mOps;
      std::vector<EntityTypePtr>    mEntities;
      ODEsolver<__EntityType>*      mSolver;
      
     
   protected:
      float                mTotalTime;
      float                mTimeDelta;
   };  

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::zeroForces()
   {
      std::vector< EntityTypePtr >::iterator it;
      for (it = mEntities.begin(); it != mEntities.end(); ++it)
      {
         (*it)->zeroForce();
      }
   }

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::execOperations()
   {
      std::list< OperatorPtr >::iterator it;
      for (it = mOps.begin(); it != mOps.end(); ++it)
      {
         ani::Operator<__EntityType>& op = *(*it);
         op.exec( *this, mTimeDelta );
      }
   }

   // get access to the list of entities so you can render them etc...
   template<class __EntityType>
   inline std::vector< boost::shared_ptr<__EntityType> >& ani::DynamicSystem<__EntityType>::entities()
   {
      return mEntities;
   }

   template<class __EntityType>
   inline const std::vector< boost::shared_ptr<__EntityType> >& ani::DynamicSystem<__EntityType>::entities() const
   {
      return mEntities;
   }

   template<class __EntityType>
   inline std::list< boost::shared_ptr< ani::Operator<__EntityType> > >& ani::DynamicSystem<__EntityType>::operators()
   {
      return mOps;
   }

   template<class __EntityType>
   inline const std::list< boost::shared_ptr< ani::Operator<__EntityType> > >& ani::DynamicSystem<__EntityType>::operators() const
   {
      return mOps;
   }

   //: add a function to the system to be executed last
   template<class __EntityType>
   inline void DynamicSystem<__EntityType>::add( boost::shared_ptr< ani::Operator<__EntityType> > op )
   {
      assert( op->isInSystem() != true && "ERROR: operator has already been added" );
      op->isInSystem( true );
      mOps.push_back( op );
   }

   //: add an entity to the system O(1)
   template<class __EntityType>
   inline void DynamicSystem<__EntityType>::add( boost::shared_ptr<__EntityType> ent )
   {
      assert( ent->isInSystem() != true && "ERROR: entity has already been added" );
      ent->isInSystem( true ); 
      mEntities.push_back( ent );
   }

   //: remove an operator from the system O(n)
   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::remove( boost::shared_ptr< ani::Operator<__EntityType> > op )
   {
      assert( op->isInSystem() != false && "ERROR: operator is not part of the system" );
      op->isInSystem( false );
      mOps.remove( op );
   }

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::clearEntities()
   {
      mEntities.clear();
   }

   template<class __EntityType>
   inline void ani::DynamicSystem<__EntityType>::clearOperators()
   {
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
   inline void ani::DynamicSystem<__EntityType>::remove( std::vector<EntityTypePtr>::iterator& it )
   {
      EntityTypePtr p = (*it);
      assert( p->isInSystem() != false && "ERROR: entity is not part of the system" );
      p->isInSystem( false );
      mEntities.erase( it );
   }
   */
      
   // return the last time delta used (or current time delta)
   template<class __EntityType>
   inline const float& ani::DynamicSystem<__EntityType>::timeDelta() const
   {
      return mTimeDelta;
   }

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
         std::vector<DynamicSystem::EntityTypePtr>::iterator it;
         for (it = mEntities.begin(); it != mEntities.end(); ++it)
         {
            EntityTypePtr entity = (*it);
            mSolver->exec( *entity, mTimeDelta );
         }
      }
   }

}; // end namespace

#endif
