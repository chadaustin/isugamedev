/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

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
