#ifndef NET_SERIALIZE_H
#define NET_SERIALIZE_H


#include <prtypes.h>
#include <string>
#include "InputStream.h"
#include "OutputStream.h"


namespace net {

  // PRUint32

  OutputStream& operator<<(OutputStream& os, PRUint32 ui) {
    os.write(&ui, 4);
    return os;
  }

  InputStream& operator>>(InputStream& is, PRUint32& ui) {
    os.read(&ui, 4);
    return is;
  }


  // std::string

  OutputStream& operator<<(OutputStream& os, const std::string& str) {
    os << PRUint32(str.length());
    os.write(str.data(), str.length());
    return os;
  }

  InputStream& operator>>(InputStream& is, std::string& str) {
    PRUint32 length;
    is >> length;
    str = std::string(length);

    // this sucks...  read into the string BUFFER_SIZE bytes at a time
    static const unsigned BUFFER_SIZE = 64;
    char buffer[BUFFER_SIZE];
    int i = 0;
    while (length > 0) {
      int read = std::min(length, BUFFER_SIZE);
      is.read(BUFFER_SIZE, read);
      std::copy_n(str.begin() + i, read, buffer);
      i += read;
      length -= read;
    }

    return is;
  }

}


#endif
