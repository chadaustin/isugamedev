/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_SERIALIZE_H
#define NET_SERIALIZE_H


#include <prtypes.h>
#include "InputStream.h"
#include "OutputStream.h"
#include <algorithm>
#include <string>


namespace net {

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
