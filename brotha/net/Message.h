#ifndef NET_MESSAGE_H
#define NET_MESSAGE_H


namespace net {

  class Message {
  public:
    virtual ~Message() { }
    virtual int getType() = 0;
    virtual void serialize(IOutputStream* os) = 0;
    virtual void deserialize(IInputStream* os) = 0;
  };

}


#endif
