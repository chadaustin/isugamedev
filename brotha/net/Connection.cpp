#include "Connection.h"

namespace net {
   Connection::Connection(Socket *socket) {
      m_socket = socket;

      m_readQueue = new MessageQueue();
      m_writeQueue = new MessageQueue();

      m_readThread = new ReadThread(socket, m_readQueue);
      m_writeThread = new WriteThread(socket, m_writeQueue);
   }

   Connection::~Connection() {
      delete m_readQueue;
      delete m_writeQueue;

      delete m_readThread;
      delete m_writeThread;
   }

   void Connection::send(Message *message) {
      m_writeQueue->push(message);
   }

   void Connection::read(std::vector<Message*> &messages) {
      m_readQueue->read(messages);
   }
}
