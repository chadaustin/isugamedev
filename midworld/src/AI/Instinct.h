#ifndef INSTINCT
#define INSTINCT


#include "Observer.h"
#include "InstinctManager.h"
#include <vector>
#include "Behavior.h"
#include <queue>
#include "BoolBehavior.h"

/**
 * This class is deisgned to be a single instinctive reaction.  It has 
 * a pure virtual function isTriggered() which is the event to test for
 * in the world and reaction is a behavior to perfrom if isTriggered is true.
 */
class Instinct : public Observer
{
public:
   Instinct(InstinctManager* s, Behavior Reaction, BoolBehavior Event)
   {
      _subject = s;
      _subject->Attach(this);
      React = Reaction;
      SetOff.ReturnType = Event.ReturnType;
   }

   virtual ~Instinct()
   {
      _subject->Detach(this);
   }

   void Update(Subject* TheChangedSubject)
   {
      if(IsTriggered())
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
   BoolBehavior SetOff;
    


private:
   InstinctManager* _subject;
   
public:



   /**
    * return true if the unit needs to react, otherwise return false
    * So each new instinct needs to make this function return true
    * if they want to trigger a reaction.
    */
   virtual bool IsTriggered()
   { 
      if(SetOff.Look() == true)
      {
         return true;
      }
      return false;
   }



};




#endif