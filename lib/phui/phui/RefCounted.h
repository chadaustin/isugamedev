/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: RefCounted.h,v $
 * Date modified: $Date: 2003-01-04 02:47:58 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#ifndef PHUI_REFCOUNTED_H
#define PHUI_REFCOUNTED_H

#include <assert.h>

namespace phui
{
   /**
    * Base class for any object that manages the number of references to itself and
    * will delete itself when it determines that it is no longer being used
    * anywhere in the application.
    */
   class RefCounted
   {
   public:
      /**
       * Creates a new reference counted object with an initial reference count
       * of zero.
       */
      RefCounted()
         : mRefCount(0)
      {}

#ifndef NDEBUG
      /**
       * When debugging is enabled, assert that there are no references to the
       * object that's being destroyed.
       */
      virtual ~RefCounted()
      {
         assert(mRefCount == 0 &&
                "Destroying an object that still has references");
      }
#endif

      /**
       * Notifies this object that the calling object has a reference to this
       * object and is using it. The reference count is incremented. Note that all
       * calls to ref() must be later followed with a call to unref().
       */
      void ref()
      {
         ++mRefCount;
      }

      /**
       * Notifies this object that the calling object has released its reference
       * to this object and no longer needs it. The reference count is decremented.
       * If the count reaches zero, this object is automagically deleted.
       */
      void unref()
      {
         assert(mRefCount > 0 && "tried to unref an object with no references");
         if (--mRefCount == 0)
         {
            delete this;
         }
      }

#ifndef NDEBUG
      /**
       * Gets the number of references currently held on this object. <b>This
       * should only be used for debugging purposes!</b>
       */
      int getRefCount() const
      {
         return mRefCount;
      }
#endif

   private:
      /**
       * A reference counted object deletes itself. Thus the delete operator is
       * made private so that you don't accidentally call delete.
       */
//      void operator delete(void* p)
//      {
//         ::operator delete(p);
//      }

   private:
      /// Gets the number of references to this object.
      int mRefCount;
   };
}

#endif
