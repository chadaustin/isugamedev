#ifndef GAME_CAR_H
#define GAME_CAR_H

#include <vector>
#include <string>
#include "Object.h"

namespace game {

   class Car {

   public:
      /// List type for Cars
      typedef std::vector<Car*> CarList;
      
      ///Iterator type
      typedef CarList::iterator CarListItr;
   
   public:

      /**
       * Creates a new player with the given name.
       */
      Car(const std::string& name);

      /**
       * Gets the name of this car.
       */
      const std::string& getName() const;

      /**
       * Adds a car to CarList
       */
      void addCar(Car* car);

      /**
       * Removes a car from CarList
       */
      void removeCar(Car* car);

   private:
      /// This player's name
      std::string mName;

      /// the existing cars
      CarList mCars;
   };

}

#endif
