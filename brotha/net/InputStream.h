#ifndef NET_INPUT_STREAM_H
#define NET_INPUT_STREAM_H


namespace net {

  class InputStream {
  public:
    virtual ~InputStream() { }
    virtual void read(void* buffer, int size) = 0;
  };

}


#endif
