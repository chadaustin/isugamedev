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
 * File:          $RCSfile: Mutex.h,v $
 * Date modified: $Date: 2002-04-28 16:41:07 $
 * Version:       $Revision: 1.10 $
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

#ifndef THREAD_MUTEX_H
#define THREAD_MUTEX_H


#include <prlock.h>
#include "Lockable.h"
#include "ThreadException.h"


namespace thread {

   class Mutex : public Lockable {
   public:
      Mutex() {
         mLock = PR_NewLock();

         if(mLock == NULL) {
            throw ThreadException("Mutex creation failed");
         }
      }

      ~Mutex() {
         PR_DestroyLock(mLock);
      }

      void lock() {
         PR_Lock(mLock);
      }

      void unlock() {
         PR_Unlock(mLock);
      }

   private:
      PRLock* mLock;
   };

} // namespace thread


#endif // THREAD_MUTEX_H
