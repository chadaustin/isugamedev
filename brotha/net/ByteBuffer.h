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
 * File:          $RCSfile: ByteBuffer.h,v $
 * Date modified: $Date: 2002-04-28 16:41:05 $
 * Version:       $Revision: 1.5 $
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

#ifndef NET_BYTE_BUFFER_H
#define NET_BYTE_BUFFER_H


#include <vector>
#include <stdlib.h>
#include <prtypes.h>
#include "InputStream.h"
#include "OutputStream.h"
#include "StreamException.h"


namespace net {

   class ByteBuffer : public InputStream, public OutputStream {
   public:
      ByteBuffer() {
         mBuffer = 0;
         mSize = 0;
      }

      ~ByteBuffer() {
         mBuffer = realloc(mBuffer, 0);
      }

      virtual void read(void* buffer, int size) {
         if (size > mSize) {
            throw StreamException("Tried to read too much from ByteBuffer!");
         }
         
         memcpy(buffer, mBuffer, size);
         memmove(mBuffer, (PRUint8*)mBuffer + size, mSize - size);
         mBuffer = realloc(mBuffer, mSize - size);
         mSize -= size;
      }
      
      virtual void write(void* buffer, int size) {
         mBuffer = realloc(mBuffer, mSize + size);
         if (mSize + size != 0 && !mBuffer) {
            throw StreamException("Out of memory!");
         }
         memcpy((PRUint8*)mBuffer + mSize, buffer, size);
         mSize += size;
      }

      int getSize() {
         return mSize;
      }

      void* getData() {
         return mBuffer;
      }
         
   private:
      void* mBuffer;
      int mSize;
   };

}


#endif
