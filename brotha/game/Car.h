#ifndef GAME_CAR_H
#define GAME_CAR_H

#include <vector>
#include <string>
#include "Object.h"

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

#endif
