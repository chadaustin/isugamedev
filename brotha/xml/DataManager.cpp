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
 * File:          $RCSfile: DataManager.cpp,v $
 * Date modified: $Date: 2002-05-03 07:00:58 $
 * Version:       $Revision: 1.3 $
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
#include "DataManager.h"
#include "xmlpersist.h"

namespace data {
   DataManager* DataManager::sInstance = NULL;

   DataManager::DataManager()
      : mFile("data.xml"), mData(NULL)
   {}

   DataManager::~DataManager() {
      flush();
      delete mData;
   }

   DataManager& DataManager::instance() {
      if (! sInstance) {
         sInstance = new DataManager();
      }
      return *sInstance;
   }

   bool DataManager::refresh()
   {
      mData = data::load(mFile);
      if (! mData) {
         std::cerr<<"Failed to load data file!"<<std::endl;
         return false;
      }
      return true;
   }

   void DataManager::flush() const {
      if (mData) {
         data::save(mData, mFile);
      }
   }

   void DataManager::setDataFile(const std::string& dataFile) {
      mFile = dataFile;
   }

   BrothaData& DataManager::getData() {
      return *mData;
   }
}
