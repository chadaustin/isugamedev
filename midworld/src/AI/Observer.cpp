#include <iostream>
#include "Observer.h"

namespace mw
{

void Subject::Attach(Observer* o) {
   _Observers.push_back(o);
}

void Subject::Detach (Observer* o) {
   std::cout << "Detach not implemented - Your stuck with it" << std::endl;
}

void Subject::Notify(){
   std::vector<Observer*>::iterator itr;
   for(itr = _Observers.begin();itr!=_Observers.end();itr++){
      (*itr)->Update(this);
   }
}

}
