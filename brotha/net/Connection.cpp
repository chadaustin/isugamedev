#include "Connection.h"

namespace net {
   Connection::Connection(auto_ptr<Socket> socket) {
      m_socket = socket;

      m_readQueue = new MessageQueue();
      m_writeQueue = new MessageQueue();

      m_readThread = new ReadThread(m_socket->getInputStream(), m_readQueue);
      m_writeThread = new WriteThread(m_socket->getOutputStream(), m_writeQueue);
   }

   Connection::~Connection() {
      m_readThread->stop();
      m_writeThread->stop();

      delete m_readQueue;
      delete m_writeQueue;

      delete m_readThread;
      delete m_writeThread;
   }

   void Connection::send(Message *message) {
      m_writeQueue->push(message);
   }

   bool Connection::read(std::vector<Message*> &messages) {
      // if the thread is still running, read the messages
      if(m_readThread->isRunning()) {
         m_readQueue->read(messages);
         return true;
      } else { // if not
         return false;
      }
   }
}
