#ifndef MW_TEST_ACTION_CONTAINER_H
#define MW_TEST_ACTION_CONTAINER_H


#include <iostream>


namespace mw{

/**
 * this class is a container class for a single action for an object to perform
 * either through a reactionary behavior (an instinct) or an assignment behavior 
 * (a behavior).
 */
class testActionContainer
{
public:
   testActionContainer(){};

   /** 
    * This function should be overriden by the client of the system.  It is the
    * action that you want an instinct to test to see if the unit should react 
    * make it return true if you want the unit to react to the instinct, 
    * make it return false if you do not want your unit to react.  
    * NOTE: this function gets called every game cycle so the perform function
    * should be optimized as much as humanly possible.  
    * the base class return false currently
    */
   virtual bool perform()
   {
      std::cout << "testActionContainer::perform - debug output - returning false" << std::endl;     
      return false;
   }

private:
};

}

#endif
