/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_STREAM_EXCEPTION_H
#define NET_STREAM_EXCEPTION_H


#include <exception>
#include <string>


namespace net {

   class SocketException : public std::exception {
   public:
      SocketException(const char* what) {
         mWhat = what;
      }

      const char* what() const {
         return mWhat.c_str();
      }
    
   private:
      std::string mWhat;
   };

}


#endif
