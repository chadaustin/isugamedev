#ifndef AIQUEUE
#define AIQUEUE

#include <queue>
#include <vector>
#include <Behavior.h>

#include <iostream>
#include <Observer.h>


class AiQueue : public Subject
{
public:
   AiQueue(){};

   virtual Behavior Peek()
   {
      return bQueue.front();
   }
   virtual void PopAndNotify()
   {
      bQueue.pop();
      Changed();
   }

   virtual void Pop()
   {
      bQueue.pop();
   }

   virtual void Push(Behavior Element)
   {
      bQueue.push(Element);
      Changed();
   }

   void Changed()
   {
      //the queue changed notify all observers
      Notify();
   }

   int Size()
   {
      return bQueue.size();
   }

private:
   std::queue<Behavior> bQueue;
};

#endif
