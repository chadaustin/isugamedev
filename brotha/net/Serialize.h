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
 * File:          $RCSfile: Serialize.h,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.13 $
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

#ifndef NET_SERIALIZE_H
#define NET_SERIALIZE_H


#include <prtypes.h>
#include "InputStream.h"
#include "OutputStream.h"
#include <algorithm>
#include <string>


namespace net {
   namespace sizes {
      inline PRUint32 getVarSize(const bool var) {
         return PRUint32(sizeof(PRUint32));
      }

      inline PRUint32 getVarSize(const PRUint32 &var) {
         return PRUint32(sizeof(PRUint32));
      }

      inline PRUint32 getVarSize(const PRFloat64 &var) {
         return PRUint32(sizeof(PRFloat64));
      }

      inline PRUint32 getVarSize(const std::string &var) {
         return PRUint32(sizeof(PRUint32) + var.length());
      }
   }

   // PRFloat64
   inline OutputStream& operator<<(OutputStream& os, PRFloat64 f) {
      os.write(&f, 8);
      return os;
   }

   inline InputStream& operator>>(InputStream& is, PRFloat64& f) {
      is.read(&f, 8);
      return is;
   }

   // PRUint32

   inline OutputStream& operator<<(OutputStream& os, PRUint32 ui) {
      os.write(&ui, 4);
      return os;
   }

   inline InputStream& operator>>(InputStream& is, PRUint32& ui) {
      is.read(&ui, 4);
      return is;
   }

   // bool (ultimately is PRUint32)

   inline InputStream& operator>>(InputStream& is, bool& b) {
      PRUint32 ui = (PRUint32)b;
      is >> ui;
      b = (ui != 0);
      return is;
   }

   // std::string

   inline OutputStream& operator<<(OutputStream& os, const std::string& str) {
      os << PRUint32(str.length());
      os.write((void*)str.data(), (int)str.length());
      return os;
   }

   inline InputStream& operator>>(InputStream& is, std::string& str) {
      PRUint32 length;
      is >> length;
      str = std::string(length, 0);

      // this sucks...  read into the string BUFFER_SIZE bytes at a time
      static const unsigned BUFFER_SIZE = 64;
      char buffer[BUFFER_SIZE];
      int i = 0;
      while (length > 0) {
         using namespace std;
         int read = min(length, BUFFER_SIZE);
         is.read(buffer, read);
         std::copy(buffer, buffer + read, str.begin() + i);
         i += read;
         length -= read;
      }

      return is;
   }

} // namespace net


#endif // NET_SERIALIZE_H
