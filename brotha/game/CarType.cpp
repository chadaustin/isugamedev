#include "CarType.h"
#include <algorithm>

namespace game {

   CarType::CarType( const std::string& name )
      : mName(name){
   }

   const std::string& CarType::getName() const
   {
      return mName;
   }

   CarType::CarTypeList CarType::getCarTypes(){
      return mCarTypes;
   }
	
}
