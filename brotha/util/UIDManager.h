/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: UIDManager.h,v $
 * Date modified: $Date: 2002-05-01 06:50:12 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */
#ifndef UIDMANAGER_H
#define UIDMANAGER_H

#include <queue>
#include <assert.h>
#include "thread/Synchronized.h"
#include "thread/Lock.h"

namespace util
{
   /**
    * A singleton class that manages unique ids for a particular object class.
    *
    * A queue is maintained with the available unique IDs. Also, the highest
    * UID allocated so far is stored.
    *
    * @param managedClass     the class for which the UIDs generated will be
    *                         unique for
    * @param id_t             the type of UIDs that will be generated
    * @param minValue         the minimum value of generated UIDs
    */
   template< class managedClass,
             class id_t = unsigned long,
             id_t minValue = 0 >
   class UIDManager : private thread::Synchronized
   {
   public:
      typedef id_t            UID;
      enum { MinValue = minValue };

      typedef std::priority_queue< UID, std::deque<UID>,
              std::greater<typename std::deque<UID>::value_type> >
              avail_queue_t;


   private:
      /**
       * This is a singleton. Use UIDManager::instance() instead.
       */
      UIDManager()
         : mLargestUID(minValue)
      {}

      /**
       * Copies of singletons are prohibited. This constructor is not implemented
       * on purpose. Usage should cause a compile-time error.
       */
      UIDManager( const UIDManager<managedClass, id_t, minValue>& copy );

      /**
       * Copies of singletons are prohibited. This assignment operator is not
       * implemented on purpose. Usage should cause a compile-time error.
       */
      UIDManager<managedClass, id_t, minValue> operator=(
                  const UIDManager<managedClass, id_t, minValue>& copy );

      /**
       * This is a singleton. You can't delete this.
       */
      virtual ~UIDManager()
      {}

   public:
      /**
       * Gets the singleton instance of this class.
       */
      static UIDManager<managedClass, id_t, minValue>& getInstance()
      {
         if ( mInstance == NULL )
         {
            mInstance = new UIDManager<managedClass, id_t, minValue>();
         }
         return *mInstance;
      }

   public:
      /**
       * Reserves a unique ID from the pool. This marks the ID as in use and is
       * guaranteed to be unique until it is released back into the pool.
       */
      UID reserveID()
      {
         thread::Lock l__(this);

         //Check if there's an ID in the available pool we can use
         if ( mAvail.size() > 0 ) {
            //Remove the next ID from the pool and reserve it
            UID id = mAvail.top();
            mAvail.pop();
            return id;
         }

         //No available IDs, we'll create a new one and reserve that
         UID id = mLargestUID++;
         return id;
      }

      /**
       * Releases the reservation on a given ID. This will mark the ID as
       * available for use by other objects.
       */
      void releaseID( const UID &id )
      {
         thread::Lock l__(this);

         //We should not be releasing IDs we are not managing!
         assert( id <= mLargestUID );

         //Add the ID back to the available pool
         mAvail.push( id );
      }

   private:
      /**
       * Pool of available IDs implemented as a priority queue. IDs that have
       * been created and used before are placed here for easier use later.
       */
      avail_queue_t mAvail;

      /**
       * The largest UID being managed by this UID manager.
       */
      UID mLargestUID;

      static UIDManager<managedClass, id_t, minValue>* mInstance;
   };

   template < class managedClass,
              class id_t,
              id_t minValue >
   UIDManager<managedClass, id_t, minValue>* UIDManager<managedClass, id_t, minValue>::mInstance = NULL;
}

#endif
