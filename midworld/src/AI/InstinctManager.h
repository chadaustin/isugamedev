#ifndef INSTINCTMAN
#define INSTINCTMAN


#include <vector>
#include <queue>


#include "Behavior.h"


#include "AINode.h"
#include "Observer.h"
#include "AiQueue.h"

class InstinctManager : public Observer, public Subject
{
public:
   
   /**
    * constructor
    */
   InstinctManager(AiQueue* bQ)
   {
      _subject = bQ;
      _subject->Attach(this);
      NumTriggers = 0;
   }


   virtual ~InstinctManager()
   {
      _subject->Detach(this);
   }
  

   /**
    * observer function for updating me of changes to the AiQueue
    * but we don't care when we recieve update because we do the updating
    * Update overrides observer base class operation
    */
   virtual void Update(Subject*)
   {
// for testing purposes you can poll the _subject here to see if it has the right value on the top of the queue
//      std::cout << "[Instinct Man]: we don't need to do anything if the queue changes" << std::endl;
//      std::cout << "[Instinct Man]: For debugging purposes here is the front element in the queue:" << std::endl;
//      std::cout << _subject->peek() << std::endl;
      
   }


   /**
    * This method updates the behavior queue in it's subject, which in 
    * our case is the behavior queue
    */
   virtual void InstinctsUpdate(){
      //_instincts.push_back(2);
      //_subject->push(_instincts.front());
      /**
       * the above two methods are from our test app
       * we actually just want to call:
       */
      Notify();
   
   }

   /**
    * this method get's called from the observer instincts when they react to something
    * and they pass it behavior b to push onto the node's queue
    */
   virtual void Reacting(Behavior b)
   {
      _subject->Push(b);
   }


private:
   int NumTriggers;  // keeps track of how many instincts have been 
                     // registered with this node
   

   std::vector<Behavior> _instincts;
   AiQueue* _subject;
};




#endif
