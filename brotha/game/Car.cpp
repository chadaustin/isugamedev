#include "Car.h"
#include <algorithm>

namespace game {

   Car::Car( const std::string& name )
      : mName(name){
   }

   const std::string& Car::getName() const
   {
      return mName;
   }
	
}
