#ifndef INSTINCT
#define INSTINCT


#include "Observer.h"
#include "InstinctManager.h"
#include <vector>
#include "Behavior.h"
#include <queue>
#include "TestActionContainer.h"


namespace mw
{


/**
 * This class is deisgned to be a single instinctive reaction.  It has 
 * a pure virtual function isTriggered() which is the event to test for
 * in the world and reaction is a behavior to perfrom if isTriggered is true.
 */
class Instinct : public Observer
{
public:
   Instinct(InstinctManager* s, Behavior Reaction, testBehavior Event)
   {
      _subject = s;
      _subject->Attach(this);
      React = Reaction;
      mTestBehavior = Event;
   }

   virtual ~Instinct()
   {
      _subject->Detach(this);
   }

   void Update(Subject* TheChangedSubject)
   {
      if(mTestBehavior.test())  // test; are we supposed to react? 
      {
         _subject->Reacting(React);
      }
   }

protected:
   /**
    * This is the function called when the AIsystem updates the node based
    * on the reaction.
    */
   Behavior React;

   /**
    * This is the function called that sets off the reaction it will return
    * and makes React register with the behavior queue
    */
   testBehavior mTestBehavior;
    


private:
   InstinctManager* _subject;
   
};

}


#endif
