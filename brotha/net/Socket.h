#if !defined(Socket_H)
#define Socket_H

#include <winsock2.h>
#include <string>

#if defined(_WIN32)
   #if !defined(errno)
      #define errno WSAGetLastError
   #endif
#else
   #define ioctlsocket ioctl
#endif

class Socket {
protected:
   SOCKET m_socket;
   struct sockaddr_in m_addrIn;
   long m_port;
   unsigned int m_polltime;

public:
   Socket();
	virtual ~Socket();

   static int getLastError();
   
   bool create(SOCKET &sock, SOCKADDR &addr);
   bool open(std::string host, long port);
   static bool initSockAddrIn(std::string &host, long port, SOCKADDR_IN &addrIn);
   void close();

   long getRecieveSize();
   bool setSocketNonBlocking();
   long send(void* buffer, unsigned long bytes2write, unsigned int timeout);
   long recieve(void* buffer, unsigned long bytes2read, unsigned int timeout);
   bool ioControl(long cmd, unsigned long *argp);

   bool isOpen();
};

#endif