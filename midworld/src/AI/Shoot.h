#ifndef SHOOT
#define SHOOT


#include <Instinct.h>
#include <Behavior.h>

#include <iostream>
#include <ShootingAction.h>

class Shoot : public BehaviorFactory
{
public:
   Shoot(){};

   virtual Behavior* MakeBehavior()
   {
      return new Behavior;
   }
   virtual ActionContainer* MakeActionContainer() const
   {
      return new ShootingAction;
   }


   
};

#endif