#ifndef NET_MESSAGE_H
#define NET_MESSAGE_H


namespace net {

  class Message {
  public:
    virtual ~Message() { }
    virtual int getType() = 0;
    virtual void serialize(OutputStream& os) = 0;
    virtual void deserialize(InputStream& os) = 0;
  };

}


#endif
