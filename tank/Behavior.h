#ifndef BEHAVIOR_H_INCLUDED
#define BEHAVIOR_H_INCLUDED

#include "RefObj.h"

//: Interface for behavior objects. A behavior object specifies the actions or
//  behavior an object may take each frame. In this way we decouple the changes
//  and object may undergo from its visual representation.
class Behavior : public RefObj
{
public:
    Behavior() {}
};

#endif // ! BEHAVIOR_H_INCLUDED
