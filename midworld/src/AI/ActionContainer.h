#ifndef MW_ACTION_CONTAINER_H
#define MW_ACTION_CONTAINER_H


#include <iostream>


namespace mw{

/**
 * this class is a container class for a single action for an object to perform
 * either through a reactionary behavior (an instinct) or an assignment behavior 
 * (a behavior).
 */
class actionContainer
{
public:
   actionContainer(){};

   /** 
    * as a user of this system when you create concrete classes with 
    * actionContainer as the base class you will need to override this
    * call with your own action, which will be the action that is performed
    */
    
   virtual void perform()
   {
      std::cout << "actionContainer::perform - debug output" << std::endl;  
   }

private:
};

}

#endif
