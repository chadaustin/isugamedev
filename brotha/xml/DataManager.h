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
 * File:          $RCSfile: DataManager.h,v $
 * Date modified: $Date: 2002-05-01 07:15:33 $
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
#ifndef DATA_DATA_MANAGER_H
#define DATA_DATA_MANAGER_H

#include "BrothaData.h"

namespace data {
   /**
    * Facade to the data subsystem. The data manager keeps an in-memory cache of
    * the database on the disk.
    */
   class DataManager {
   public:
      /**
       * Creates a new data manager using the given database.
       */
      DataManager(const std::string& dataFile);

      /**
       * Flushes data out and destroys the data manager.
       */
      ~DataManager();

      /**
       * Flushes out the data in memory to the disk.
       */
      void flush() const;

      /**
       * Gets the data in memory.
       */
      BrothaData& getData();

   private:
      /// The file in which the data is stored.
      std::string mFile;

      /// The in memory cache of the data.
      BrothaData* mData;
   };
}

#endif
