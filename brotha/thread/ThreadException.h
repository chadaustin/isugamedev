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
