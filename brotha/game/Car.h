//#ifndef CAR_H
//#define CAR_H

#include <string>
#include "Object.h"
#include <vector>

namespace game {

   class Car {
   public:

      /**
       * Creates a new player with the given name.
       */
      Car(const std::string& name);

      /**
       * Gets the name of this car.
       */
      const std::string& getName() const;

   private:
      /// This player's name
      std::string mName;

   };

}
