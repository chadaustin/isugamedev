
//////////////////////////////////////////////////////////////////
//
//                         -=     Kevin's Queue     =-
//
// Definition: "allows you to see if an item is in the queue,
//              the STL queue doesn't allow this, that is why
//              this queue is implemented with an STL list"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: kqueue.h,v $
//    $Date: 2002-01-30 06:18:27 $
//    $Revision: 1.2 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
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

//////////////////////////////////////////////////////////////////////////////
#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED

#include <list>

namespace kev
{

   template<class Data>
   class queue
   {
   public:
       //default constructor.
       queue();

       //destructor
       // NOTE: does not delete data
       ~queue();

       // get a reference to the oldest object on the queue.
       Data& last();

       // get a const reference to the oldest object on the queue.
       const Data& last() const;

       // remove the oldest item from the queue.
       // NOTE: does not 'delete' data
       void dequeue()
       {
          _queue.pop_front();
       }

       // check to see if an item is present in the queue.
       bool isPresent(const Data& item) const;

       // insert an item into the queue.
       void enqueue( const Data& item )
       {
          _queue.push_back(item);
       }

       //clear the queue.
       // NOTE: does not delete data
       void clear();

       //return the size.
       inline int size() const { return _queue.size(); }

   protected:
	   std::list<Data> _queue;
   };


   template<class Data>
   inline queue<Data>::queue()
   {
   }

   template<class Data>
   inline queue<Data>::~queue()
   {
   }

   // get a reference to the current object on the queue.
   template<class Data>
   inline Data& queue<Data>::last()
   {
       return _queue.front();
   }

   // get a const reference to the current object on the queue.
   template<class Data>
   inline const Data& queue<Data>::last() const
   {
       return _queue.front();
   }

   // check to see if an item is present in the queue.
   template<class Data>
   inline bool queue<Data>::isPresent(const Data& item) const
   {
       list<Data>::const_iterator itemIT;
       for(itemIT = _queue.begin(); itemIT != _queue.end(); ++itemIT)
       {
	   //found a match
	   if( item == *itemIT )
	       return true;
       }

       //couldn't find a match
       return false;
   }

   //clear the queue.
   // NOTE: does not delete data
   template<class Data>
   inline void queue<Data>::clear()
   {
       _queue.clear();
   }
};

#endif
