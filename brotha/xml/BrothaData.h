#ifndef DATA_BROTHA_DATA_H
#define DATA_BROTHA_DATA_H

#include <iostream>
#include <string.h>
#include <vector>

#include "Car.h"
#include "Gang.h"
#include "CarType.h"
#include "Player.h"
#include "ModType.h"

namespace data {

   class BrothaData {
   public:
      /// Gets the list of gangs in the database.
      GangList& getGangList() {
         return mGangs;
      }

      /// Gets the list of car types in the database.
      CarTypeList& getCarTypes() {
         return mCarTypes;
      }

	  ModTypeList& getModTypes(){
		  return mModTypes;
	  }
      /// Adds the given car type to the database.
      void addCarType(CarType* c) {
         mCarTypes.push_back(c);
      }

	  void addModType(ModType* m){
		  mModTypes.push_back(m);
	  }

      /// Adds the given gang to the database.
      void addGang(Gang* g) {
         mGangs.push_back(g);
      }

      void xMLify(std::ostream& out) {
         out << "<wbdata>" << std::endl;
         for (unsigned int i = 0; i < mGangs.size(); ++i) {
            mGangs[i]->xMLify(out);
         }
         for (unsigned int i = 0; i < mCarTypes.size(); ++i) {
            mCarTypes[i]->xMLify(out);
         }
		 for (unsigned int i = 0; i < mModTypes.size(); ++i){
			   mModTypes[i]->xMLify(out);
		 }
         out << "</wbdata>";
      }

      /// Gets the gang with the given name in the database.
      Gang* getGang(const std::string& name) {
         for (unsigned int i = 0; i < mGangs.size(); ++i) {
            if (mGangs[i]->getName() == name) {
               return mGangs[i];
            }
         }
         throw "not found";
         return mGangs[0];  //should never be reached.
      }

      /// Gets the player with the given name in the database or NULL if not found.
      Player* getPlayer(const std::string& name) {
         GangList::iterator itr;
         for (itr = mGangs.begin(); itr != mGangs.end(); ++itr) {
            if (Player* p = (*itr)->getPlayer(name)) {
               return p;
            }
         }
         return NULL;
      }

   private:
      /// All gangs in the database.
      GangList mGangs;

      /// All car types in the database.
      CarTypeList mCarTypes;

	  ModTypeList mModTypes;
   };
}

#endif
