#ifndef MW_BEHAVIOR_H
#define MW_BEHAVIOR_H

#include <iostream>
#include "ActionContainer.h"
#include "TestActionContainer.h"

namespace mw
{

/**
 * Base behavior class
 */
class Behavior 
{
public:
   Behavior(){};
    
   virtual void addActionContainer(actionContainer* AC)
   {
      actions.push_back(AC);
   }

   /**
    * TODO: reimplement this function so that it handles multiple actions
    */
   std::vector<actionContainer*> getAction(){
      return actions;
   }

private:
   std::vector<actionContainer*> actions;
};

/**
 * testBehavior class is used in an instinct function
 * the user of the system should add the testactioncontainer for the
 * test they are performing.
 */
class testBehavior
{
public:
   testBehavior(){};

   virtual void addTestActionContainer(testActionContainer TAC)
   {
      testAction = TAC;
   }

   bool test()
   {
      return testAction.perform();
   }
private:
   testActionContainer testAction;
};

/*
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
*/

/*
Behavior* CreateBehavior(BehaviorFactory &Factory){
   Behavior* TheBehavior = Factory.MakeBehavior();
   ActionContainer* TheAction = Factory.MakeActionContainer();
   TheBehavior->AddActionContainer(TheAction);
   return TheBehavior;
}

*/
}


#endif
