/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef THREAD_THREAD_EXCEPTION_H
#define THREAD_THREAD_EXCEPTION_H


#include <exception>
#include <string>


namespace thread {

   class ThreadException : public std::exception {
   public:
      ThreadException(const char* what) {
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
