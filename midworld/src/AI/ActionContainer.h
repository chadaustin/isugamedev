#ifndef ACTIONCON
#define ACTIONCON


#include <iostream>


/**
 * this class is a container class for a single action for an object to perform
 * either through a reactionary behavior (an instinct) or an assignment behavior 
 * (a behavior).
 */
class ActionContainer
{
public:
   ActionContainer(){};

   /** 
    * as a user of this system when you create concrete classes with 
    * actionContainer as the base class you will need to override this
    * call with your own action, which will be the action that is performed
    */
    
   virtual void Perform()
   {
      std::cout << "default Action - you didn't override this did you" << std::endl;  
   }

private:
};

#endif