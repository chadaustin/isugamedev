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

   void Car::addCar(Car* car){
      mCars.push_back(car);
   }

   void Car::removeCar(Car* car){
      CarListItr Itr;

      // find the player to delete and set to iterator 
      Itr = std::find(mCars.begin(),mCars.end(),car);
      
      // makes sure object exists, then removes if it does
      if (Itr != mCars.end()){
         mCars.erase(Itr);
      }
   }
	
}
