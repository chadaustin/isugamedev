#ifndef BOOLBEH
#define BOOLBEH

#include <iostream>


class BoolBehavior
{
public:
   BoolBehavior(){ ReturnType = true; }
   
   virtual void SetTrue(){ ReturnType = true; }
   virtual void SetFalse(){ ReturnType = false; }

   virtual bool Look(){ return ReturnType; }


   bool ReturnType;
};
#endif