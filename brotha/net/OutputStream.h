#ifndef NET_OUTPUT_STREAM_H
#define NET_OUTPUT_STREAM_H


namespace net {

   class OutputStream {
   public:
      virtual ~OutputStream() { }
      virtual void write(void* buffer, int size) = 0;
   };

} // namespace net


#endif // NET_OUTPUT_STREAM_H
