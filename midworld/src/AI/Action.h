#ifndef ACTION
#define ACTION

#include <Observer.h>
#include <queue>
#include <AiQueue.h>
#include <AINode.h>


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
    * it overrides observer base class operation
    *
    * So what I need to do is peek at the first element in the queue
    * and start performing that behavior.
    */
   virtual void Update(Subject* newQueue)
   {
      if (_subject->Size() == 1)
      {
         _subject->Peek().GetAction()->Perform();
      }else
      {
         _subject->Peek().GetAction()->Perform();
         _subject->Pop();         
      }
   }    

private:
   AiQueue* _subject;

   
};



#endif