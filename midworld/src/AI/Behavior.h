#ifndef BEHAVIOR
#define BEHAVIOR

#include <iostream>
#include "ActionContainer.h"

class Behavior 
{
public:
   Behavior(){};
   
   virtual void AddActionContainer(ActionContainer* AC)
   {
      Actions = AC;
   }
   ActionContainer* GetAction(){
      return Actions;
   }

private:
   ActionContainer* Actions;
};


class BehaviorFactory
{
public:
   BehaviorFactory(){};

   virtual Behavior* MakeBehavior()
   {
      return new Behavior;
   }
   virtual ActionContainer* MakeActionContainer() const
   {
      return new ActionContainer;
   }
};



Behavior* CreateBehavior(BehaviorFactory &Factory){
   Behavior* TheBehavior = Factory.MakeBehavior();
   ActionContainer* TheAction = Factory.MakeActionContainer();
   TheBehavior->AddActionContainer(TheAction);
   return TheBehavior;
}





#endif