#ifndef NET_STREAM_EXCEPTION_H
#define NET_STREAM_EXCEPTION_H


#include <exception>
#include <string>


namespace net {

  class StreamException : public std::exception {
  public:
    StreamException(const char* what) {
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
