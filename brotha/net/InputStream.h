/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_INPUT_STREAM_H
#define NET_INPUT_STREAM_H


namespace net {

   class InputStream {
   public:
      virtual ~InputStream() { }
      virtual void read(void* buffer, int size) = 0;
   };

} // namespace net


#endif // NET_INPUT_STREAM_H
