#ifndef ACTION
#define ACTION

#include "Observer.h"
#include <queue>
#include "AiQueue.h"
#include "AINode.h"


namespace mw
{

class Action : public Observer
{
public:
   Action(AiQueue* bQ)
   {
      _subject = bQ;
      _subject->Attach(this);
   }

   virtual ~Action()
   {
      _subject->Detach(this);
   }

   /**
    * observer function for updating me of changes to the AiQueue
    * but we don't care when we recieve update we only update it
    * this method overrides observer base class operation
    *
    * So what I need to do is peek at the first element in the queue
    * and start performing that behavior.
    */
   virtual void Update(Subject* newQueue)
   {
      if (_subject->Size() == 1)
      {
         _subject->Peek().getAction().front()->perform();
      }else
      {
         _subject->Peek().getAction().front()->perform();
         _subject->Pop();         
      }
   }    

private:
   AiQueue* _subject;

   
};

}

#endif
