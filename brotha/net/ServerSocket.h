#if !defined(ServerSocket_H)
#define ServerSocket_H

#include "socket.h"

class ServerSocket : public Socket
{
protected:
   long m_numQueued;
public:
   ServerSocket(long _numQueued);
   virtual ~ServerSocket();

   bool open(long port);
   bool listen();
   bool accept(Socket &socket);
};

#endif