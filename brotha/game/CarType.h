#ifndef GAME_CARTYPE_H
#define GAME_CARTYPE_H

#include <vector> 
#include <string>
#include "Object.h"

namespace game {

   class CarType {

   public: 
      /// Vector for list of car types
      typedef std::vector<CarType*> CarTypeList;
   
   public:

      /**
       * Creates a new player with the given name.
       */
      CarType(const std::string& name);

      /**
       * Gets the name of this car.
       */
      const std::string& getName() const;

      /**
       * Gets a list of the available car types
       */
      CarTypeList getCarTypes();

   private:
      /// This player's name
      std::string mName;

      /// List of Car types
      CarTypeList mCarTypes;

   };

}

#endif
