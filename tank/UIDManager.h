#ifndef UIDMANAGER_H_INCLUDED
#define UIDMANAGER_H_INCLUDED

#include <queue>
#include "Singleton.h"

//: A singleton class that manages unique ids for a particular object class.
//
//  A queue is maintained with the available unique IDs. Also, the highest
//  UID allocated so far is stored. 
template < class managedClass,
           class id_t = unsigned long >
class UIDManager : public kev::Singleton< UIDManager<managedClass> >
{
public:
   typedef id_t            UID;
   typedef std::priority_queue< UID, std::deque<UID>,
           std::greater<typename std::deque<UID>::value_type> >
           avail_queue_t;
                                   

public:
   //: This is a singleton. Use UIDManager::instance() instead
   UIDManager()
   {
      mLargestUID = 0;
   }

   //: This is a singleton. You can't delete this.
   virtual ~UIDManager()
   {
   }

public:
   //: Reserves a unique ID from the pool. This marks the ID as in use and is
   //  guaranteed to be unique until it is released back into the pool.
   UID reserveID()
   {
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

   //: Releases the reservation on a given ID. This will mark the ID as
   //  available for use by other objects.
   void releaseID( const UID &id )
   {
      //We should not be releasing IDs we are not managing!
      assert( id <= mLargestUID );

      //Add the ID back to the available pool
      mAvail.push( id );
   }

private:
   //: Pool of available IDs implemented as a priority queue. IDs that have been
   //  created and used before are placed here for easier use later.
   avail_queue_t mAvail;

   //: The largest UID being managed by this UID manager.
   UID mLargestUID;
};

#endif // ! UIDMANAGER_H_INCLUDED
